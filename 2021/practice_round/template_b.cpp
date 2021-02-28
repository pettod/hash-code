#include <vector>
#include <map>
#include <cstdio>
#include <cmath>
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <set>
#include <sstream>
#include <functional>
#include <iterator>
#include <random>
#include <list>
#include <queue>
#include <cstdlib>
#include <string>
#include <memory.h>
#include <cstdint>
#include <unordered_map>
#include <unordered_set>
#include <cassert>
#include <bitset>
#include <fstream>
#include <deque>
#include <cmath>
#include <numeric>
#include <stack>
#include <stdarg.h>
#include <cstdio>
#include <stdlib.h>
#include <stdio.h>

using namespace std;
#define fi(n) for (int i = 0; i < int (n); i++)
#define fj(n) for (int j = 0; j < int (n); j++)
#define fk(n) for (int k = 0; k < int (n); k++)
#define f1(_n) for (auto&i1 : _n)
#define f2(_n) for (auto&i2 : _n)
#define f3(_n) for (auto&i3 : _n)
#define all(n) n.begin(), n.end()
#define break(_x)    {_x;break;}
#define continue(_x) {_x;continue;}
#define _sort(_x)    sort(_x.begin(), _x.end())
#define r_sort(_x)   sort(_x.rbegin(), _x.rend())
#define MAX_VAL_OF(_x) std::numeric_limits<decltype(_x)>::max()


int sum(vector<int> v)
{
    int total = 0;
    fi(v.size()) total += v[i];
    return total;
}


float mean(vector<int> v)
{
    return sum(v) / v.size();
}


float standardDeviation(vector<int> v)
{
    float mu = mean(v);
    float s = 0;
    fi(v.size()) s += pow(v[i] - mu, 2);
    return sqrt(s / v.size());
}


tuple<vector<pair<int, vector<int>>>, int, int, int> readFile(string file_name="a_example")
{
    vector<pair<int, vector<int>>> a;
    map<string, int> ingredient_map;
    int m, t2, t3, t4;
    int pizza_index = 0;
    fstream file;
    file.open(file_name, ios::in);
    file >> m >> t2 >> t3 >> t4;

    while (m--)
    {
        int number_of_ingredients;
        file >> number_of_ingredients;
        vector<int> pizza_ingredients;
        string ingredient;
        fj(number_of_ingredients)
        {
            file >> ingredient;
            map<string, int>::iterator ingredient_it =
                ingredient_map.find(ingredient);
            if (ingredient_it == ingredient_map.end())
            {
                ingredient_map.insert({ingredient, ingredient_map.size()});
                pizza_ingredients.push_back(ingredient_map.size());
            }
            else
                pizza_ingredients.push_back(ingredient_it->second);
        }
        sort(pizza_ingredients.begin(), pizza_ingredients.end());
        a.push_back({pizza_index, pizza_ingredients});
        ++pizza_index;
    }
    file.close();
    auto sort_order = [](auto& i, auto& j) {
        return i.second.size() < j.second.size(); };
    sort(all(a), sort_order);
    tuple<vector<pair<int, vector<int>>>, int, int, int> w = {a, t2, t3, t4};
    return w;
}

void writeFile(vector<vector<int>> a, string file_name="a_solution")
{
   ofstream file;
   file.open(file_name);
   file << a.size() << "\n";
   fi(a.size())
   {
      fj(a[i].size())
      {
         file << a[i][j];
         if (j < a[i].size() - 1) file << " ";
      }
      file << "\n";
   }
   file.close();
}

bool sort_int(const int& i, const int& j) { return i < j; }

int findBestPizza(
   vector<pair<int, vector<int>>>& b,
   int number_of_compared_pizzas,
   int bi,
   vector<int> comparison)
{
   vector<int> best_points;
   fi(min((int)b.size(), number_of_compared_pizzas))
   {
      int points = 0;
      fj(b[bi-i].second.size())
      {
         bool q = binary_search(
            comparison.begin(),
            comparison.end(),
            b[bi-i].second[j],
            sort_int);
         if (!q) ++points;
      }
      best_points.push_back(points);
   }
   std::vector<int>::iterator max = max_element(
      best_points.begin(), best_points.end());
   int argmax = distance(best_points.begin(), max);
   return argmax;
}

void solve(string in_file, string out_file)
{
   tuple<vector<pair<int, vector<int>>>, int, int, int> a = readFile(in_file);
   vector<vector<int>> solution;
   vector<pair<int, vector<int>>> b = get<0>(a);
   int t2 = get<1>(a);
   int t3 = get<2>(a);
   int t4 = get<3>(a);
   int number_of_pizzas = b.size();
   int number_of_compared_pizzas = 100;

   while (t2-- && b.size() >= 2)
   {
      vector<int> comparison = b[b.size() - 1].second;
      int index_0 = b[b.size() - 1].first;
      b.pop_back();
      int bi = b.size() - 1;
      int argmax = findBestPizza(b, number_of_compared_pizzas, bi, comparison);
      solution.push_back({2, index_0, b[bi-argmax].first});
      b.erase(b.end() - argmax - 1);
   }
   while (t3-- && b.size() >= 3)
   {
      vector<int> comparison = b[b.size() - 1].second;
      int index_0 = b[b.size() - 1].first;
      b.pop_back();
      int bi = b.size() - 1;
      int argmax = findBestPizza(b, number_of_compared_pizzas, bi, comparison);
      int index_1 = b[bi-argmax].first;
      comparison.insert(
         comparison.end(),
         b[bi-argmax].second.begin(),
         b[bi-argmax].second.end());
      sort(comparison.begin(), comparison.end());
      b.erase(b.end() - argmax - 1);
      bi = b.size() - 1;
      argmax = findBestPizza(b, number_of_compared_pizzas, bi, comparison);
      int index_2 = b[bi-argmax].first;
      solution.push_back({3, index_0, index_1, index_2});
      b.erase(b.end() - argmax - 1);
   }
   while (t4-- && b.size() >= 4)
   {
      vector<int> comparison = b[b.size() - 1].second;
      int index_0 = b[b.size() - 1].first;
      b.pop_back();

      int bi = b.size() - 1;
      int argmax = findBestPizza(b, number_of_compared_pizzas, bi, comparison);
      int index_1 = b[bi-argmax].first;
      comparison.insert(
         comparison.end(),
         b[bi-argmax].second.begin(),
         b[bi-argmax].second.end());
      sort(comparison.begin(), comparison.end());
      b.erase(b.end() - argmax - 1);

      bi = b.size() - 1;
      argmax = findBestPizza(b, number_of_compared_pizzas, bi, comparison);
      int index_2 = b[bi-argmax].first;
      comparison.insert(
         comparison.end(),
         b[bi-argmax].second.begin(),
         b[bi-argmax].second.end());
      sort(comparison.begin(), comparison.end());
      b.erase(b.end() - argmax - 1);

      bi = b.size() - 1;
      argmax = findBestPizza(b, number_of_compared_pizzas, bi, comparison);
      int index_3 = b[bi-argmax].first;

      solution.push_back({4, index_0, index_1, index_2, index_3});
      b.erase(b.end() - argmax - 1);
   }
   writeFile(solution, out_file);
}


int main()
{
   vector<string> in_files = {
      "input_files/a_example",
      "input_files/b_little_bit_of_everything.in",
      "input_files/c_many_ingredients.in",
      "input_files/d_many_pizzas.in",
      "input_files/e_many_teams.in"
   };
   vector<string> out_files = {
      "a_solution.txt",
      "b_solution.txt",
      "c_solution.txt",
      "d_solution.txt",
      "e_solution.txt",
   };
   fi(in_files.size())
      solve(in_files[i], out_files[i]);
}
