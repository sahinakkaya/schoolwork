/* @Author
* Student Name: Şahin Akkaya
* Student ID : 150170098
* Date: 08/11/2018 */
#include "lang_model.h"
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <locale>
#include <string>
#include <vector>
//#include <codecvt> // If ssh had this library, my program would work perfectly.
// Currently it can't handle when a turkish character is given in command-line.

using namespace std;

wchar_t to_lower(int c);
int StringToWString(wchar_t& wc, const string& s);
int index_of(int c);

int main(int argc, char* argv[])
{
    language_model lm;
    lm.vocabularylist = new vocab_list;

    if (argc >= 2) {
        lm.readData(argv[1]);
        if (argc == 2)
            lm.print();
        else if (argc == 4) {
            string current_exec_name = argv[0];
            string first_arge;
            vector<string> all_args;
            if (argc > 1) {
                first_arge = argv[1];
                all_args.assign(argv + 1, argv + argc);
            }
            wcout << lm.calculateProbability(all_args[1], all_args[2]) << endl;

        } else {
            cerr << "You should enter exactly 1 or 3 command line argument(s), " << argc - 1 << " given." << endl;
            return -1;
        }
    } else {
        cerr << "You should enter exactly 1 or 3 command line argument(s), " << argc - 1 << " given." << endl;
        return -1;
    }
    return 0;
}

int StringToWchar(wchar_t& wc, const string& s)
{

    wstring ws(s.size(), L' ');
    ws.resize(std::mbstowcs(&ws[0], s.c_str(), s.size()));
    wc = ws[0];
    return 0;
}

/* This function could be used if ssh had codecvt library.
The above function doesn't work on non-ascii chars, unfortunetely.*/
/*
wstring stringToWstring(const string& t_str)
{
    typedef codecvt_utf8 <wchar_t> convert_type;
    wstring_convert<convert_type, wchar_t> converter;
    return converter.from_bytes(t_str);
}*/

wchar_t to_lower(int c)
{
    wstring uppercase = L"ABCÇDEFGĞHIİJKLMNOÖPQRSŞTUÜVWXYZ";
    wstring lowercase = L"abcçdefgğhıijklmnoöpqrsştuüvwxyz";
    for (int i = 0; i < (int)uppercase.size(); i++) {
        if (uppercase[i] == c) {
            return lowercase[i];
        }
    }
    return c;
}
int index_of(int c)
{
    wstring s = L"abcçdefgğhıijklmnoöpqrsştuüvwxyz0123456789";
    for (int i = 0; i < (int)s.size(); i++) {
        if (c == s[i])
            return i;
    }
    return (int)s.size() + 1;
}

bool vocab_node::is_exists(wchar_t c)
{
    occur_node* t = list;
    while (t) {
        if (t->character == c) {
            return true;
        }
        t = t->next;
    }
    return false;
}

bool vocab_list::is_exists(wchar_t c)
{
    vocab_node* t = head;
    while (t) {
        if (t->character == c)
            return true;
        t = t->next;
    }
    return false;
}

int vocab_list::find_insert_point(wchar_t c)
{
    vocab_node* t = head;
    int index = 0;
    if (is_exists(c))
        return -1;
    while (t) {
        if (index_of(t->character) > index_of(c))
            return index;
        index++;
        t = t->next;
    }
    return nodecount;
}

int vocab_node::get_node_number(wchar_t c)
{
    occur_node* t = list;
    int index = 0;
    while (t) {
        if (t->character == c) {
            return index;
        }
        index++;
        t = t->next;
    }
    return -1;
}

void vocab_list::add_occurence(wchar_t a, wchar_t b)
{
    a = to_lower(a);
    b = to_lower(b);
    vocab_node* t = head;
    while (t) {
        if (t->character == a) {
            break;
        }
        t = t->next;
    }

    occur_node* newnode = new occur_node;
    newnode->character = b;
    newnode->next = NULL;
    newnode->occurence = 1;

    int nodenum = t->get_node_number(b);

    occur_node* tt = t->list;
    if (nodenum >= 0) {
        while (nodenum > 0) {
            tt = tt->next;
            nodenum--;
        }
        tt->occurence++;
        delete newnode;
    } else {
        if (tt) {
            while (tt->next) {
                tt = tt->next;
            }
            tt->next = newnode;
        } else
            t->list = newnode;
        t->nodecount++;
    }
}

void vocab_list::add_char(wchar_t c)
{
    c = to_lower(c);
    vocab_node* newnode = new vocab_node;
    newnode->character = c;
    newnode->list = NULL;
    newnode->nodecount = 0;
    int insert_point = this->find_insert_point(c);
    vocab_node* t = head;
    if (insert_point >= 0) {
        if (insert_point) {
            while (insert_point > 1) {
                t = t->next;
                insert_point--;
            }
            newnode->next = t->next;
            t->next = newnode;
        } else {
            newnode->next = head;
            head = newnode;
        }
        nodecount++;

    } else
        delete newnode;
}

void vocab_list::print()
{
    vocab_node* t = head;
    while (t) {
        if (t->character == L' ')
            wcout << "<SP>:" << endl;
        else
            wcout << t->character << ":" << endl;
        occur_node* o = t->list;
        while (o) {
            wcout << L"\t<";
            if (o->character == L' ')
                wcout << "<SP>";
            else
                wcout << o->character;
            wcout << L", " << o->occurence << L">" << endl;
            o = o->next;
        }
        t = t->next;
    }
}
void vocab_list::create()
{
    head = NULL;
    nodecount = 0;
}

int vocab_list::get_occurence(wchar_t a)
{
    vocab_node* t = head;
    if (is_exists(a)) {
        while (t) {
            if (t->character == a) {
                break;
            }
            t = t->next;
        }
        occur_node* tt = t->list;
        int count = 0;
        while (tt) {
            count += tt->occurence;
            tt = tt->next;
        }
        return count;

    } else
        return -1;
}

int vocab_list::get_union_occurence(wchar_t a, wchar_t b)
{
    vocab_node* t = head;
    while (t) {
        if (t->character == a) {
            break;
        }
        t = t->next;
    }
    occur_node* tt;
    if (t)
        tt = t->list;
    else
        tt = NULL;
    while (tt) {
        if (tt->character == b)
            return tt->occurence;
        tt = tt->next;
    }
    return 0;
}

void language_model::readData(const char* filename)
{
    ios::sync_with_stdio(false);
    locale loc("en_US.UTF-8");
    wcout.imbue(loc);
    wfstream file(filename);
    file.imbue(loc);

    vocabularylist->create();

    wstring line;
    while (getline(file, line)) {
        int line_size = (int)line.size();
        if (line[0]) {
            int i;
            for (i = 0; i < line_size; i++) {
                vocabularylist->add_char(line[i]);
            }
        }
    }
    file.clear();
    file.seekg(0, ios::beg);
    file.imbue(loc);
    while (getline(file, line)) {
        int line_size = (int)line.size();
        if (line[0]) {
            int i;
            for (i = 1; i < line_size; i++) {
                vocabularylist->add_occurence(line[i - 1], line[i]);
            }
            vocabularylist->add_occurence(line[line_size - 1], L' ');
        }
    }
    file.close();
}
void language_model::print()
{
    vocabularylist->print();
}

double language_model::calculateProbability(const std::string& x, const std::string& y)
{
    wchar_t a, b;
    StringToWchar(a, x);
    StringToWchar(b, y);

    /* Please comment above 3 lines and uncomment these 2 if you have codecvt library.
    This works perfect! :)
    wchar_t a = stringToWstring(x)[0];
    wchar_t b = stringToWstring(y)[0];*/

    a = to_lower(a);
    b = to_lower(b);

    int a_count = vocabularylist->get_occurence(a);
    int ab_count = vocabularylist->get_union_occurence(a, b);
    if (a_count > 0) {
        return ((double)ab_count) / a_count;
    } else {
        if (!a_count && !ab_count) {
            wcerr << L"There might be a problem with your input file." << endl;
            wcerr << L"Try inserting some spaces between words!" << endl;
            wcerr << L"If you still want to know the result, here it is:" << endl;
        }
        return 0;
    }
    return 0;
}