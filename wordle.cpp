#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void helper(
    const string& in,
    string current,
    const set<string>& dict,
    set<string>& results,
    string floating,
    int index)
{
    if(index == (int)in.size())
    {
        if(dict.find(current) != dict.end() && floating.empty())
        {
            results.insert(current);
        }
        return;
    }

    if(in[index] != '-')
    {
        current.push_back(in[index]);
        helper(in, current, dict, results, floating, index+1);
    }
    else
    {
        int blanksLeft = 0;
        for(int i = index; i < (int)in.size(); ++i)
        {
            if(in[i] == '-') blanksLeft++;
        }

        set<char> options;
        if((int)floating.size() >= blanksLeft)
        {
            for(char c : floating) options.insert(c);
        }
        else
        {
            for(char c = 'a'; c <= 'z'; ++c) options.insert(c);
        }

        for(char c : options)
        {
            string next = current + c;
            string nextFloating = floating;
            size_t pos = nextFloating.find(c);
            if(pos != string::npos)
            {
                nextFloating.erase(pos,1);
            }
            helper(in, next, dict, results, nextFloating, index+1);
        }
    }
}



// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    set<string> results;
    helper(in, "", dict, results, floating, 0);
    return results;
}

// Define any helper functions here
