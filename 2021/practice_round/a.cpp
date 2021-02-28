#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <stdio.h>
#include <math.h>
#include <tuple>
#include <map>

using namespace std;


tuple<vector<pair<int, vector<int>>>, int, int, int> readFile(string file_name="a_example")
{
   vector<pair<int, vector<int>>> a;
   map<string, int> ingredient_map;
   int m, t2, t3, t4;
   int pizza_index = 0;
   fstream file;
   file.open(file_name, ios::in);
   file >> m >> t2 >> t3 >> t4;

   if (file.is_open())
   {
      while (m--)
      {
         int number_of_ingredients;
         file >> number_of_ingredients;
         vector<int> pizza_ingredients;
         string ingredient;
         for (int j=0; j<number_of_ingredients; ++j)
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
   }
   auto sort_order = [](auto& i, auto& j) {
      return i.second.size() < j.second.size(); };
   sort(a.begin(), a.end(), sort_order);
   tuple<vector<pair<int, vector<int>>>, int, int, int> w = {a, t2, t3, t4};
   return w;
}

void writeFile(vector<vector<int>> a, string file_name="a_solution")
{
   ofstream file;
   file.open(file_name);
   file << a.size() << "\n";
   for (int i=0; i<a.size(); ++i)
   {
      for (int j=0; j<a[i].size(); ++j)
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
   for (int i=0; i<min((int)b.size(), number_of_compared_pizzas); ++i)
   {
      int points = 0;
      for (int j=0; j<b[bi-i].second.size(); ++j)
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
   for (int i=0; i<in_files.size(); ++i)
      solve(in_files[i], out_files[i]);
}
