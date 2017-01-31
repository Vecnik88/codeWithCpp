// Реализован пользовательский класс
// для ввода текста и отбраковка его от повторяющихся слов, а также символов

// ### Created Vecnik88 30.12.2016 ###

// It implemented a custom class
// To enter text and its rejection of the repeated words and symbols

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>

using namespace std;

class Punct_stream              // <---. Аналогичен istream, но пользователь может задавать пробельные символы
{
public:
    Punct_stream(istream& is):source{is}, sensitive{true}{}

    void whitespace(const string& s)    // <---. делает s, строкой пробельных символов
    {
        white = s;
    }
    void add_white(char c)      // <---. добавляет символ в набор пробельных
    {
        white +=c;
    }
    bool is_whitespace(char c); // <---. входит ли символ в набор пробельных символов

    void case_sensitive(bool b){sensitive = b;}
    bool is_case_sensitive(){return sensitive;}

    Punct_stream& operator >>(string& s);
    operator bool()             // <---. возможность неявного преобразования Punct_stream в тип bool
    {
        return !(source.fail() || source.bad()) && source.good();
    }
private:
    istream& source;            // <---. источник символов
    istringstream buffer;       // <---. буфер для форматирования
    string white;               // <---. пробельные символы
    bool sensitive;             // <---. чувствителен поток к регистру?
};

Punct_stream& Punct_stream::operator>>(string& s)
{
    while(!(buffer>>s))
    {
        if(buffer.bad() || !source.good()) return *this;
        buffer.clear();

        string line;
        getline(source,line);   // <---. считываем строку полностью с пробелами

        for(char& ch:line)
            if(is_whitespace(ch))
                ch =' ';        // <---. преобразуем в пробел
            else if(!sensitive)
                ch=tolower(ch); // <---. преобразуем в нижний регистр

        buffer.str(line);       // <---. записываем строку в поток
    }
    return *this;
}

bool Punct_stream::is_whitespace(char c)
{
    for(char& x: white)
        if(c==x)return true;
    return false;
}
int main()
{
    Punct_stream ps(cin);
    ps.whitespace(";:,.?!()\"{}<>/&$@#%^*|~");              // <---. символы которых не должно быть
    ps.case_sensitive(false);

    cout << "\t### Enter word ###" << endl;
    vector<string> vs;
    for(string word; ps>>word;)
        vs.push_back(word);

    sort(vs.begin(), vs.end());                             // <---. сортируем полученные слова

    for(int i{0}; i<vs.size(); ++i)                         // <---. выводим на экран полученные слова
        if(i==0 || (vs[i]!=vs[i-1])) cout << vs[i] << endl; // <---. убираем дубликаты при выводе

    return 0;
}
