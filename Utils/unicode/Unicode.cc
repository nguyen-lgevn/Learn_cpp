#include <iostream>
#include <locale>

int utf8_to_unicode(std::string utf8_code);
std::string unicode_to_utf8(int unicode);

int main()
{
#if 0
    for (int i = 21; i < 256; i++)
    {
        std::cout << unicode_to_utf8(i) << "\n";    
    }
#endif
    //std::cout << unicode_to_utf8(36) << "\t";    
    //std::cout << unicode_to_utf8(162) << "\t";

    
    //std::cout << unicode_to_utf8(8364) << "\t";    
    std::cout << "\U1FA00" << std::endl;
}

int utf8_to_unicode(std::string utf8_code)
{
    unsigned int utf8_size = utf8_code.length();
    int unicode = 0;

    for (unsigned p = 0; p < utf8_size; ++p)
    {
        int bit_count = (p? 6: 8 - utf8_size - (utf8_size == 1 ? 0 : 1)), 
            shift = (p < utf8_size - 1 ? (6*(utf8_size - p - 1)): 0);
        for (int k = 0; k < bit_count; ++k)
        {
            unicode += ((utf8_code[p] & (1 << k)) << shift);
        }
    }
}

std::string unicode_to_utf8(int unicode)
{
    std::string s;
    if ((unicode >= 0) && (unicode <= 0x7f))
    {
        s = static_cast<char>(unicode);
        return s;
    }
    else if (unicode <= 0x7ff)
    {
        unsigned char c1 = 192, c2 = 128;
        for (int k = 0; k < 11; ++k)
        {
            if (k < 6) c2 |= (unicode % 64) & (1 << k);
            else c1 |= (unicode >> 6) & (1 << (k-6));
        }
        std::cout << c1 << " -  " << c2 << std::endl;
        s = c1;
        s+= c2;
        return s;
    }
    else if (unicode <= 0xffff)
    {
        unsigned char c1 = 224, c2 = 128, c3 = 128;
        for (int k = 0; k < 16; ++k)
        {
            if (k < 6) c3 |= (unicode % 64) & (1 << k);
            else if (k < 12) c2 |= (unicode >> 6) & (1 << (k-6));
            else c1 |= (unicode >> 12) & (1 << (k-12));            
        }
        s = c1;
        s += c2;
        s += c3;
        return s;
    }
    else if (unicode <= 0x1fffff)
    {
        unsigned char c1 = 240, c2 = 128, c3 = 128, c4 = 128;
        for (int k = 0; k < 21; ++k)
        {
            if (k < 6) c4 |= (unicode % 64) & (1 << k);
            else if (k < 12) c3 |= (unicode >> 6) & (1 << (k-6));
            else if (k < 18) c2 |= (unicode >> 12) & (1 << (k-12));
            else c1 |= (unicode >> 18) & (1 << (k-18));            
        }
        s = c1;
        s += c2;
        s += c3;
        s += c4;
        return s;
    }
    else if (unicode < 0x3ffffff)
    {
        ;
    }
    else if (unicode <= 0x7fffffff)
    {
        ;
    }
    else
    {
        ;
    }
    return "";
}
