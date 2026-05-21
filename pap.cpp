#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <fstream>

void Skaitymas (std::map<std::string, int>& zds);
void spausdint (std::map<std::string, int>& zds);
bool isrinktURL(std::string zodis);
void galas (std::string &zodis);

int main (){

    std::map<std::string, int> zds;
    int kiek = 0;

    Skaitymas(zds);
    spausdint(zds);
    return 0;
}
void Skaitymas (std::map<std::string, int>& zds)
{

    std::string zodis;
    std::ifstream fd ("tests.txt");
    if (!fd.is_open())
    {
        std::cout << "Failas neatsidare" << std::endl;
        return;
    }
    while (fd >> zodis)
    {
        if (zds.find(zodis) == zds.end())
        {
            galas(zodis);
            zds.insert({zodis, 1});
            if (isrinktURL(zodis) == true)
            {
                zds.erase(zodis);
            }
            
        }
        else
        {
            zds[zodis]++;
        }
    }
    fd.close();
}
void spausdint (std::map<std::string, int>& zds)
{
    std::ofstream fr ("rezultatai.txt");
    for (const auto& [zodis, kiekis] : zds)
    {
        fr << std::setw(20) << std::left << zodis << " " << kiekis << '\n';
    }
    fr.close();
}
bool isrinktURL(std::string zodis)
{
    int kiek = 0;
    int sk = zodis.size();
    for (int i = 0; i < sk; i++)
    {
        if (zodis[i] == '.') kiek++;
    }
    for (int i = 0; i < sk; i++) 
    {
        if (kiek > 1) return true;
        if (kiek == 1 && zodis[sk - 1] != '.') return true;
        if (zodis[i] == '/' || zodis[i] == '\\')
        {
            return true;
        }
    }
    return false;
}
void galas (std::string &zodis)
{
    int sk = zodis.size();
    if (zodis[sk-1] == '.' || zodis[sk-1] == ',' || zodis[sk-1] == '!' || zodis[sk-1] == '?' || zodis[sk-1] == ';' || zodis[sk-1] == ':' || zodis[sk-1] == '%' || zodis[sk-1] == '"' || zodis[sk-1] == '\'' || zodis[sk-1] == ')' || zodis[sk-1] == ']' || zodis[sk-1] == '}' || zodis[sk-1] == '-' || zodis[sk-1] == '_')
    {
        zodis.erase(sk-1, 1);
    }
    else if (zodis[0] == '.' || zodis[0] == ',' || zodis[0] == '!' || zodis[0] == '?' || zodis[0] == ';' || zodis[0] == ':' || zodis[0] == '%' || zodis[0] == '"' || zodis[0] == '\'' || zodis[0] == '(' || zodis[0] == '[' || zodis[0] == '{' || zodis[0] == '-' || zodis[0] == '_')
    {
        zodis.erase(0, 1);
    }
}
