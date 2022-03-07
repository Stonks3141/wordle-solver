#include <string>
#include <map>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>

std::string find_best_word(std::vector<std::string> &guesses, std::vector<std::string> &answers)
{
    auto best_guess = std::string();
    auto best_guess_count = 0;
    if(answers.size() <= 2)
    {
        return answers[0];
    }

    for(auto& guess : guesses)
    {
        auto elim_ctr = 0.0;

        auto colors = std::map<std::vector<int>, int>();

        for(auto& answer : answers)
        {
            auto color = std::vector{0, 0, 0, 0, 0};
            for(auto i = 0; i < 5; ++i)
            {
                if(guess[i] == answer[i])
                    color[i] = 2;
                else if(answer.find_first_of(guess[i]) != std::string::npos)
                    color[i] = 1;
            }
            colors[color]++;
        }

        for(auto& [color, count] : colors)
        {
            auto elims = 0;
            for(auto& answer : answers)
            {
                for(auto i = 0; i < 5; ++i)
                {
                    if((color[i] == 2 && answer[i] != guess[i]) ||
                            (color[i] == 1 && answer.find_first_of(guess[i]) == std::string::npos) ||
                            (color[i] == 0 && answer.find_first_of(guess[i]) != std::string::npos))
                    {
                        elims++;
                        break;
                    }
                }
            }
            elim_ctr += elims * count;
        }


        auto thing = elim_ctr / answers.size();

        if(thing > best_guess_count)
        {
            best_guess = guess;
            best_guess_count = thing;
        }
    }

    //std::cout << "Best guess avg: " << best_guess_count << "\n";
    //std::cout << "Best guess: " << best_guess << "\n";

    return best_guess;
}

std::vector<std::string> thing(std::vector<std::string> &guesses, std::vector<std::string> &answers, std::string answer, std::string guess)
{
    auto new_answers = answers;

    auto color = std::vector<int>{0, 0, 0, 0, 0};
    for(auto i = 0; i < 5; ++i)
    {
        if(guess[i] == answer[i])
            color[i] = 2;
        else if(answer.find_first_of(guess[i]) != std::string::npos)
            color[i] = 1;
    }

    new_answers.erase(std::remove_if(new_answers.begin(), new_answers.end(),
                                     [color, guess](std::string answer2){
        for(auto i = 0; i < 5; ++i)
        {
            if(
                    (color[i] == 2 && answer2[i] != guess[i]) ||
                    (color[i] == 1 && answer2.find_first_of(guess[i]) == std::string::npos) ||
                    (color[i] == 0 && answer2.find_first_of(guess[i]) != std::string::npos)
                    )
            {
                return true;
            }
        }
        return false;
    }), new_answers.end());

    std::cout << "new size: " << new_answers.size() << "\n";

    if(new_answers.size() == 1)
    {
        std::cout << new_answers[0] << " ";
        return {new_answers[0]};
    }
    else
    {
        auto t = find_best_word(guesses, new_answers);
        std::cout << t << " ";
        if(t == answer)
        {
            return {t};
        }
        auto r = thing(guesses, new_answers, answer, t);
        r.insert(r.begin(), t);
        if(r.size() > 100)
        {
            std::cout << "uhoh\n";
            exit(1);
        }
        return r;
    }
}

int main(int argc, char const *argv[])
{
    auto answers = std::vector<std::string>{};
    auto guesses = std::vector<std::string>{};

    auto ansfile = std::ifstream("answers.txt");
    auto guessfile = std::ifstream("guesses.txt");

    if(!ansfile || !guessfile)
    {
        std::cout << "file issue\n";
        exit(1);
    }

    auto str = std::string();

    while(std::getline(ansfile, str))
    {
        answers.push_back(str);
    }

    str.clear();
    while(std::getline(guessfile, str))
    {
        guesses.push_back(str);
    }

    auto speed = std::map<int, int>();
    /*
    for(auto& ans : answers)
    {
        std::cout << "roate ";
        auto a = thing(guesses, answers, ans, "roate");
        std::cout << "\n";
        speed[a.size()]++;
    }
    */
    auto a = thing(guesses, answers, "heath", "roate");
    for(auto& [num, ct] : speed)
    {
        std::cout << ct << " Wordles solved in " << num << " tries\n";
    }

    return 0;
}
