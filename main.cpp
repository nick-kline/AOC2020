#include <iostream>
#include <fstream>
#include <array>
#include <algorithm>

int main()
{
    std::ifstream ifile;
    ifile.open("input.txt");

    if(!ifile.bad())
    {
        const unsigned columns = 8;
        const unsigned rows = 128;
        std::array<std::size_t, columns * rows> seatids{0};
        auto lastseat = seatids.begin();
        auto firstseat = seatids.end();

        for(std::string bsid; std::getline(ifile, bsid);)
        {
            std::size_t seatid = 0;
            std::size_t size = columns * rows;
            for(auto i : bsid)
            {
                size /= 2;
                seatid += (i == 'B' || i == 'R') ? size : 0;
            }
            seatids[seatid] = seatid;
            auto current = std::next(seatids.begin(), seatid);
            lastseat = (current > lastseat) ? current : lastseat;
            firstseat = (current < firstseat) ? current : firstseat;
        }
        std::cout << "Highest seat id: " << *lastseat << std::endl;

        auto seat = std::find(firstseat, lastseat, 0);
        if(seat != seatids.end())
        {
            std::cout << "Missing id: " << seat - seatids.begin() << std::endl;
        }
    }
    return 0;
}
