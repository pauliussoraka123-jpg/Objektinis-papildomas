#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <set>

struct INFO{
    std::set<int> eilutes;
    int kiekis = 0;
};

void Skaitymas (std::map<std::string, INFO>& zds, std::unordered_set<std::string>& urls, std::unordered_set<std::string>& tld);
void spausdint (const std::map<std::string, INFO>& zds, const std::unordered_set<std::string>& urls);
bool isrinktURL(const std::string& zodis, const std::unordered_set<std::string>& tld);
void galas (std::string &zodis);
void loadURL(std::unordered_set<std::string>& tld, std::ifstream& fd);

int main (){

    std::unordered_set<std::string> tld;
    std::map<std::string, INFO> zds;
    std::unordered_set<std::string> urls;
    std::ifstream fd ("URLS.txt");
    if (!fd.is_open())
    {
        std::cout << "Failas neatsidare" << std::endl;
        return 1;
    }
    loadURL(tld , fd);


    Skaitymas(zds, urls, tld);
    spausdint(zds, urls);
    return 0;
}
void Skaitymas (std::map<std::string, INFO>& zds, std::unordered_set<std::string>& urls, std::unordered_set<std::string>& tld)
{
    std::string zodis;
    std::ifstream fd ("tests.txt");
    if (!fd.is_open())
    {
        std::cout << "Failas neatsidare" << std::endl;
        return;
    }
    std::string eile;
    int nr = 0;
    
    while (std::getline(fd, eile))
    {
        nr++;
        std::stringstream ss(eile);
        while (ss >> zodis)
        {
        galas(zodis);

        if (zodis.empty()) continue;

        if (isrinktURL(zodis, tld))
        {
            for (char& c : zodis)c = std::tolower(static_cast<unsigned char>(c));
            urls.insert(zodis);
            continue;
        }
        else 
        {
            for (char& c : zodis)c = std::tolower(static_cast<unsigned char>(c));
            zds[zodis].eilutes.insert(nr);
            zds[zodis].kiekis++;
        }
        }
    }
    fd.close();
}

void spausdint (const std::map<std::string, INFO>& zds, const std::unordered_set<std::string>& urls)
{
    std::ofstream fr ("rezultatai.txt");
    for (const auto& [zodis, INFO] : zds)
    {
        if (INFO.kiekis > 1) 
        {
            fr << std::setw(20) << std::left << zodis;
            fr << "Kiekis: " << std::setw(5) << std::left << INFO.kiekis;
            fr << "Eilutės: ";
            for (const auto& eilute : INFO.eilutes)
            {
                fr << eilute << ' ';
            }
            fr << '\n';
        }
    }
    fr << "\nURL -ai:\n";
    for (const auto& url : urls)
    {
        fr << url << '\n';
    }
    fr.close();
}
bool isrinktURL(const std::string& zodis, const std::unordered_set<std::string>& tld)
{
    if (zodis.find('.') != std::string::npos || zodis.find('/') != std::string::npos || zodis.find(':') != std::string::npos)
    {    
    size_t dot = zodis.rfind('.');
    if (dot == std::string::npos || dot == zodis.size() - 1)
    {
        return false;
    }
    size_t slash = zodis.find('/', dot);
    std::string galas;
        if (slash != std::string::npos)
        {
            galas = zodis.substr(dot + 1, slash - dot - 1);
        }
        else
        {
            galas = zodis.substr(dot + 1);
        }

        for (char& c : galas) c = std::toupper(static_cast<unsigned char>(c));

        if (tld.find(galas) != tld.end())
        {
            return true;
        }
        else {
            return false;
        }
    }
    else {
        return false;
    }
    return false;
}
void galas(std::string &zodis) {
    std::string skirykliai = ".,!?;:%\\()[]{}-_−—-–\"«»<>/*-+&|^~`@#$^=\\\'1234567890"; 

    while (!zodis.empty() && skirykliai.find(zodis.back()) != std::string::npos) {
        zodis.pop_back();
    }

    while (!zodis.empty() && skirykliai.find(zodis.front()) != std::string::npos) {
        zodis.erase(0, 1);
    }

}
void loadURL(std::unordered_set<std::string>& tld, std::ifstream& fd)
{
    std::string s;
    while (fd >> s)
    {
        for (char& c : s)
            c = std::toupper(static_cast<unsigned char>(c));

        tld.insert(s);
    }
}