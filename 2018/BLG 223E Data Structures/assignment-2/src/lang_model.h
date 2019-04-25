#include <string>
class occur_node {
    public:
        wchar_t character;
        occur_node* next;
        int occurence;
};

class vocab_node{
    public:
        int nodecount;
        wchar_t character;
        vocab_node* next;
        occur_node* list;
        bool is_exists(wchar_t);
        int get_node_number(wchar_t);

};

class vocab_list{
    int nodecount;
    vocab_node* head;
    public:
        void create();
        void print();
        void add_char(wchar_t );
        void add_occurence(wchar_t , wchar_t );
        int get_occurence(wchar_t );
        int get_union_occurence (wchar_t , wchar_t );
        bool is_exists(wchar_t);
        int find_insert_point(wchar_t);
};
class language_model{
    
    public:
        vocab_list* vocabularylist;
        void print();
        void readData(const char*);
        double calculateProbability (const std::string&, const std::string&);

};
