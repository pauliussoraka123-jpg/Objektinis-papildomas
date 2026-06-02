#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <fstream>
#include <vector>
#include <unordered_set>
#include <sstream>
#include <set>
#include <cctype>

struct INFO{
    std::set<int> eilutes;
    int kiekis = 0;
};

void Skaitymas (std::map<std::string, INFO>& zds, std::unordered_set<std::string>& urls, std::unordered_set<std::string>& tld);
void spausdint (const std::map<std::string, INFO>& zds, const std::unordered_set<std::string>& urls);
bool isrinktURL(const std::string zodis, const std::unordered_set<std::string>& tld);
void galas (std::string &zodis);
void loadURL(std::unordered_set<std::string>& tld, std::ifstream& fd);
void galasurl(std::string &zodis);

int main (){

    std::unordered_set<std::string> tld;
    std::map<std::string, INFO> zds;
    std::unordered_set<std::string> urls;
    std::ifstream fd ("URLS.txt");
    if (!fd.is_open())
    {
        std::cout << "URL Failas neatsidare" << std::endl;
        return 1;
    }
    loadURL(tld , fd);
    fd.close();

    Skaitymas(zds, urls, tld);
    spausdint(zds, urls);
    return 0;
}
void Skaitymas (std::map<std::string, INFO>& zds, std::unordered_set<std::string>& urls, std::unordered_set<std::string>& tld)
{
    std::string filename;
    std::cout << "Esami failai:" << '\n';
    system ("powershell ls *.txt");
    std::cout << "Iveskite failo pavadinima:" << '\n';
    std::cin >> filename;
    std::ifstream fd(filename);
    try {
        if (!fd.is_open()) {
            throw std::runtime_error("Nepavyko atidaryti failo: " + filename);
        }
    }
    catch (const std::exception& e) {
        std::cout << "Klaida: " << e.what() << '\n';
        return;
    }

    std::string zodis;
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
        galasurl(zodis);

        if (zodis.empty()) continue;

        if (isrinktURL(zodis, tld))
        {
            for (char& c : zodis)c = std::tolower(static_cast<unsigned char>(c));
            urls.insert(zodis);
            continue;
        }
        else 
        {
            galas(zodis);
            if (zodis.empty()) continue;
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
bool isrinktURL(const std::string zodis, const std::unordered_set<std::string>& tld)
{
    if (zodis.find("www.") == 0 || zodis.find("http://") == 0 || zodis.find("https://") == 0)
    {
        return true;
    }

    std::string domenas = zodis;
    size_t slash = domenas.find('/');
    if (slash != std::string::npos) domenas = domenas.substr(0, slash);
    


    size_t taskas = domenas.size();
    if (zodis.find('.') != std::string::npos || zodis.find('/') != std::string::npos || zodis.find(':') != std::string::npos)
    {
        while ((taskas = domenas.rfind('.', taskas-1)) != std::string::npos)
        {
        std::string galas = domenas.substr(taskas + 1);

        for (char& c : galas) c = std::toupper(static_cast<unsigned char>(c));

        if (tld.find(galas) != tld.end())
        {
            return true;
        }
        if (taskas == 0) break;
    }
    }
    else {
        return false;
    }
    return false;
}
void galas(std::string &zodis) {
    std::string skirykliai = ".,!?;:%\\()[]{}-_−—-–\"«»<>/*-+&|^~`@#$^=\\\'1234567890 "; 

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
void galasurl(std::string &zodis) {
    std::string skirykliai = ".,!?;:%\\()[]{}-_−—-–\"«»<>/*-+&|^~`@#$^=\\\' "; 

    while (!zodis.empty() && skirykliai.find(zodis.back()) != std::string::npos) {
        zodis.pop_back();
    }

    while (!zodis.empty() && skirykliai.find(zodis.front()) != std::string::npos) {
        zodis.erase(0, 1);
    }

}