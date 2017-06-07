#include "parser.h"

#ifdef _DEBUG
#include <iostream>
#endif

namespace dominion{ namespace parser {
    decltype(dominion::parser::counts_) dominion::parser::counts_{};

    struct_turnline
        parse_turnline(std::string& str) {

        decltype(parse_turnline(str)) ret;

#ifdef _DEBUG
        std::cout << "[" << str << "]" << std::endl;
#endif
        std::stringstream linestream(str);

        std::string verb;
        linestream >> ret.playerID >> verb; /// possible for playerID to have space
        // next token should be a (set of) verb(s)
        try {
            ret.verb = parse_verb(verb);
        } catch (...) {
            std::cout << "\b! caught parse_verb exception";
            std::cin.get();
        }
        
        const static std::map<verb_tokens, std::string> verb_supplements =
        {
            { verb_tokens::Buy  , " and gains " },
            { verb_tokens::React, " with "      },
            { verb_tokens::Look , " at "        },
            { verb_tokens::Start, " with "      },
        };

        auto expect = [&linestream](std::string const& str)->bool {
            auto save_pos = linestream.tellg();

            bool good = true;
            for (auto const& i : str) {
                if ((char)linestream.get() != i || !linestream.good()){
                    good = false;
                    break;
                }
            }
            
            if (!good)
                linestream.seekg(save_pos); // return to saved stream position

            return good;
        };

        auto f = verb_supplements.find(ret.verb);
        if (f != verb_supplements.end()) {
            auto& vstr = verb_tokens_map.right.at(f->first);
            if (expect(f->second))
                ++counts_[vstr + f->second];
            else
            {
                std::cerr << "\b! \"" << vstr << "\" but not \"" << f->second << "\"";
                std::cin.get();
            }
        }

        if (ret.verb == verb_tokens::Shuffle)
            return ret; //end of line assumed ".. shuffles their deck"
        
        // rest of line is set of cards
        try {
            ret.cards = parse_cards(linestream);
        } catch (...) {
            std::cout << "\b! caught parse_cards exception";
            std::cin.get();
        }

        return ret;
    }

    verb_tokens
        parse_verb(std::string& str) {
        
        auto verb_find = verb_tokens_map.left.find(str);
        if (verb_find != verb_tokens_map.left.end())
        {   
            ++counts_[verb_find->first];
            return verb_find->second;
        }

#ifdef _DEBUG
        std::cerr << "couldnt find verb for: [" << str << "]";
        std::cin.get();
#endif
        throw;
    }

    std::vector<pair_card_num>
        parse_cards(std::istream& istr) {
        
        decltype(parse_cards(istr)) ret{};

        std::string str;
        while (istr >> str) 
        {
            if (str == "and") // "and" continues the collection
                continue;

            //1. number part of pair
            auto num = parse_card_num(str);

            //2. card part of pair
            std::string str_card;
            istr >> str_card;
            // ignore ',' as final character
            if (!str_card.empty() && str_card.back() == ',')
                str_card.pop_back();
            // singular-ize
            auto sing_find = singular.find(str_card);
            if (sing_find != singular.end())
                str_card = sing_find->second;
            // get card token
            auto card_find = card_tokens_map.left.find(str_card);
            if (card_find != card_tokens_map.left.end()) {
                ++counts_[card_find->first];
                //append the <num,card> pair to return
                ret.emplace_back(num, card_find->second);
            } 
#ifdef _DEBUG
            else {
                std::cerr << "\b! couldnt find card: [" << str_card << "]";
                std::cin.get();
                throw;
#endif
            }
        }

        return ret;
    }

    unsigned short
        parse_card_num(std::string& str)
    {
        if (str == "a" || str == "an") {
            return 1;
        }
        //else
        unsigned short i;
        try {
            i = (unsigned short)std::stoi(str);
        } catch (...) {
            std::cout << "\b! caught exception from stoi on string: " << str << std::endl;
            std::cin.get();
            i = 0;
        }
        return i;
    }
}} // namespace dominion::parser