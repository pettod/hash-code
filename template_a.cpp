#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>
#include <set>
#include <stdio.h>
#include <math.h>
#include <tuple>

using namespace std;


tuple<vector<vector<int>>, int, int, int> readFile(string file_name="a_example")
{
   vector<vector<int>> a;
   int m, t2, t3, t4;
   fstream file;
   file.open(file_name, ios::in);

   file >> m >> t2 >> t3 >> t4;
   int pizza_index = 0;
   if (file.is_open())
   {
      while (m--)
      {
         int number_of_ingredients;
         file >> number_of_ingredients;
         string ingredient;
         for (int j=0; j<number_of_ingredients; ++j)
         {
            file >> ingredient;
         }
         a.push_back({pizza_index, number_of_ingredients});
         ++pizza_index;
      }
      file.close();
   }
   auto sort_order = [](vector<int>& i, vector<int>& j) { return i[1] > j[1]; };
   sort(a.begin(), a.end(), sort_order);
   tuple<vector<vector<int>>, int, int, int> w = {a, t2, t3, t4};
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


void solve(string in_file, string out_file)
{
   tuple<vector<vector<int>>, int, int, int> a = readFile(in_file);
   vector<vector<int>> solution;
   vector<vector<int>> b = get<0>(a);
   int t2 = get<1>(a);
   int t3 = get<2>(a);
   int t4 = get<3>(a);
   int number_of_pizzas = b.size();
   int i = 0;
   int j = min(t2-1, number_of_pizzas - 1);
   int t2_org = t2;
   int t3_org = t3;
   while (t2-- && j-i >= 2)
   {
      solution.push_back({2, b[i][0], b[j][0]});
      i += 1;
      j -= 1;
   }
   i = t2_org;
   j = min(t2_org+t3-1, number_of_pizzas - 1);
   while (t3-- && j-i >= 3)
   {
      solution.push_back({3, b[i][0], b[i+1][0], b[j][0]});
      i += 2;
      j -= 1;
   }
   i = t3_org + t2_org;
   j = number_of_pizzas - 1;
   while (t4-- && j-i >= 4)
   {
      solution.push_back({4, b[i][0], b[i+1][0], b[j][0], b[j-1][0]});
      i += 2;
      j -= 2;
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
