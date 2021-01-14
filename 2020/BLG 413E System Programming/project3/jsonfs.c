/*
 * jsonfs - Displays the contents of a JSON file as a directory using FUSE.
 *
 * 150150014 Ezgi Hasret Açıkgöz
 * 150160128 Emek Gözlüklü
 * 150170098 Şahin Akkaya
 * 
 * Compile: 
 * Download cJSON.c and cJSON.h from https://github.com/DaveGamble/cJSON
 * and put them in the same directory as this file.
 * gcc -Wall -Werror jsonfs.c cJSON.c -D_FILE_OFFSET_BITS=64 -lfuse -o jsonfs
 */

#define FUSE_USE_VERSION 26

static const char* jsonfsVersion = "2021.01.14";

#include <assert.h>
#include <errno.h>
#include <fuse.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include "cJSON.h"

// Global variables to store filename and root of the tree
char* filename;
cJSON* root;

/******************************
 *
 * Helper functions
 *
 ******************************/
void read_file_and_initalize_json() {
  char* buffer = 0;
  long length;
  FILE* f = fopen(filename, "rb");

  if (f) {
    fseek(f, 0, SEEK_END);
    length = ftell(f);
    fseek(f, 0, SEEK_SET);
    buffer = malloc(length);
    if (buffer) {
      fread(buffer, 1, length, f);
    }
    fclose(f);
  }
  root = cJSON_Parse(buffer);
  free(buffer);
}
int get_depth(const char* path) {
  int i;
  const char* tmp = path;
  if (strcmp(path, "/") == 0) {
    return 0;
  }
  for (i = 0; tmp[i]; tmp[i] == '/' ? i++ : *tmp++)
    ;
  return i;
}

char** split_path(const char* path) {
  int i = get_depth(path);
  int j;
  int k = 1;
  char** dirs = malloc(sizeof(char*) * i);
  for (j = 0; j < i; j++) {
    dirs[j] = malloc(sizeof(char) * strlen(path) + 1);
    int l = 0;
    if (strcmp(path, "/") == 0) {
      return dirs;
    }
    while (path[k] != '/' && path[k] != '\0') {
      dirs[j][l++] = path[k];
      k++;
    }
    dirs[j][l] = '\0';
    k++;
  }
  return dirs;
}

cJSON* find_sibling_with_name(cJSON* node, const char* name) {
  while (strcmp(node->string, name) != 0) {
    if (node->next)
      node = node->next;
    else
      return NULL;
  }
  return node;
}
cJSON* find_child_with_name(cJSON* node, const char* name) {
  if (node->child == NULL) {
    return NULL;
  }
  node = node->child;
  return find_sibling_with_name(node, name);
}

cJSON* go_to_path(const char* path) {
  cJSON* node = root;
  char* current_dir;
  char** dirs = split_path(path);  // class, operatingsystems
  int len_dirs = get_depth(path);
  int i = 0;
  while (i < len_dirs) {
    current_dir = dirs[i];
    node = find_child_with_name(node, current_dir);
    if (node == NULL)
      return NULL;
    i += 1;
  }
  for (i = 0; i < len_dirs; i++)
    free(dirs[i]);
  free(dirs);
  return node;
}
char* trim_path(const char* path) {
  char** dirs = split_path(path);
  int len_dirs = get_depth(path);
  int i = 0;
  char* new_path = malloc(sizeof(char) * strlen(path));
  strcpy(new_path, "/");
  while (i < len_dirs - 1) {
    strcat(new_path, dirs[i]);
    strcat(new_path, "/");
    i++;
  }
  if (i != 0) {
    new_path[strlen(new_path) - 1] = '\0';
  }
  return new_path;
}

int get_num_of_dirs(cJSON* node){
    int num_of_dirs = 0;
    node = node->child;
    while(node != NULL){
        int is_dir = cJSON_IsObject(node);
        num_of_dirs += is_dir;
        node = node->next;
    }
    return num_of_dirs;
}
/******************************
 *
 * Callbacks for FUSE
 *
 ******************************/

enum {
  KEY_HELP,
  KEY_VERSION,
};

static int jsonfs_getattr(const char* path, struct stat* stbuf) {
  int res = 0;

  memset(stbuf, 0, sizeof(struct stat));
  if (strcmp(path, "/") == 0) {
    stbuf->st_mode = S_IFDIR | 0755;
    stbuf->st_nlink = get_num_of_dirs(root) + 2;
    stbuf->st_size = 4096;
  } else {
    // "/class/operatingsystems

    // "/abcd/efgh
    cJSON* node = go_to_path(path);
    if (node == NULL)
      return -ENOENT;
    int is_dir = cJSON_IsObject(node);
    if (is_dir) {
      stbuf->st_mode = S_IFDIR | 0755;
      stbuf->st_nlink = get_num_of_dirs(node) + 2;
      stbuf->st_size = 4096;
    } else {
      stbuf->st_mode = S_IFREG | 0444;
      stbuf->st_nlink = 1;
      stbuf->st_size = strlen(node->valuestring);
    }

  }
  stbuf->st_uid = getuid();
  stbuf->st_gid = getgid();

  return res;
}
static int jsonfs_readdir(const char* path,
                          void* buf,
                          fuse_fill_dir_t filler,
                          off_t offset,
                          struct fuse_file_info* fi) {
  cJSON* node = root;
  cJSON* child;
  (void)offset;
  (void)fi;

  if (strcmp(path, "/") == 0) {
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    child = node->child;
    while (child != NULL) {
      filler(buf, child->string, NULL, 0);
      child = child->next;
    }

  } else {
    // "/club/basketball"
    node = go_to_path(path);
    if (node == NULL)
      return -ENOENT;
    filler(buf, ".", NULL, 0);
    filler(buf, "..", NULL, 0);
    child = node->child;
    while (child != NULL) {
      filler(buf, child->string, NULL, 0);
      child = child->next;
    }
  }
  return 0;
}

static int jsonfs_read(const char* path,
                       char* buf,
                       size_t size,
                       off_t offset,
                       struct fuse_file_info* fi) {
  cJSON* node = go_to_path(path);
  size_t len;
  (void)fi;
  len = strlen(node->valuestring);
  if (offset < len) {
    if (offset + size > len)
      size = len - offset;
    memcpy(buf, node->valuestring + offset, size);
  } else
    size = 0;
  return size;
}

static int jsonfs_mkdir(const char* path, mode_t mode) {
  char** dirs = split_path(path);
  int len_dirs = get_depth(path);

  char* trimmed_path = trim_path(path);
  cJSON* node = go_to_path(trimmed_path);
  free(trimmed_path);

  cJSON* new_dir = cJSON_CreateObject();
  cJSON_AddItemToObject(node, dirs[len_dirs - 1], new_dir);
  for (int i = 0; i < len_dirs; i++)
    free(dirs[i]);
  free(dirs);

  char* string = cJSON_Print(root);
  FILE* file = fopen(filename, "w");
  fputs(string, file);
  fclose(file);
  return 0;
}
static struct fuse_operations jsonfs_oper = {
    .getattr = jsonfs_getattr,
    .readdir = jsonfs_readdir,
    .mkdir = jsonfs_mkdir,
    .read = jsonfs_read,
};
static void usage(const char* progname) {
  fprintf(
      stdout,
      "usage: %s jsonfilename mountpoint [options]\n"
      "\n"
      "   Displays the contents of a JSON file as a directory at mountpoint\n"
      "\n"
      "general options:\n"
      "   -o opt,[opt...]     mount options\n"
      "   -h  --help          print help\n"
      "   -V  --version       print version\n"
      "\n",
      progname);
}

static int jsonfs_parse_opt(void* data,
                            const char* arg,
                            int key,
                            struct fuse_args* outargs) {
  (void)data;

  switch (key) {
    case FUSE_OPT_KEY_NONOPT:
      if (filename == 0) {
        filename = strdup(arg);
        return 0;
      } else {
        return 1;
      }
    case FUSE_OPT_KEY_OPT:
      return 1;
    case KEY_HELP:
      usage(outargs->argv[0]);
      exit(0);
    case KEY_VERSION:
      fprintf(stdout, "jsonfs version %s\n", jsonfsVersion);
      exit(0);
    default:
      fprintf(stderr, "see `%s -h' for usage\n", outargs->argv[0]);
      exit(1);
  }
  return 1;
}

static struct fuse_opt jsonfs_opts[] = {
    FUSE_OPT_KEY("-h", KEY_HELP), FUSE_OPT_KEY("--help", KEY_HELP),
    FUSE_OPT_KEY("-V", KEY_VERSION), FUSE_OPT_KEY("--version", KEY_VERSION),
    FUSE_OPT_END};

int main(int argc, char* argv[]) {
  struct fuse_args args = FUSE_ARGS_INIT(argc, argv);
  int res;

  res = fuse_opt_parse(&args, &filename, jsonfs_opts, jsonfs_parse_opt);
  if (res != 0) {
    fprintf(stderr, "Invalid arguments\n");
    fprintf(stderr, "see `%s -h' for usage\n", argv[0]);
    exit(1);
  }
  if (filename == 0) {
    fprintf(stderr, "Missing filename\n");
    fprintf(stderr, "see `%s -h' for usage\n", argv[0]);
    exit(1);
  }

  printf("file: %s\n", filename);

  read_file_and_initalize_json();
  fuse_main(args.argc, args.argv, &jsonfs_oper, NULL);

  return 0;
}
