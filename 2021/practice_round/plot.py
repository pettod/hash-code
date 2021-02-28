from os import listdir
from os.path import isfile, join
import numpy as np
import matplotlib.pyplot as plt


def extractFile(file_name):
    m = 0
    t2 = 0
    t3 = 0
    t4 = 0
    number_of_ingredients_per_pizza = []
    different_ingredients = set()

    with open(file_name) as file:
        lines = file.readlines()
        for i, line in enumerate(lines):
            if line == '\n':
                continue
            if i == 0:
                line = [ int(x) for x in line[:-2].split(' ') ]
                m = line[0]
                t2 = line[1]
                t3 = line[2]
                t4 = line[2]
            else:
                ingredients = line.split(' ')
                number_of_ingredients_per_pizza.append(int(ingredients[0]))
                different_ingredients.update(ingredients[0:])
    return m, t2, t3, t4, number_of_ingredients_per_pizza, different_ingredients


def main():
    root = "input_files"
    txt_files = sorted([
        join(root, f) for f in listdir(root) if isfile(join(root, f))])
    print(txt_files)
    grid_x = 2
    grid_y = 2
    for txt_file in txt_files:
        m, t2, t3, t4, number_of_ingredients_per_pizza, \
            different_ingredients = extractFile(txt_file)
        i = 1
        fig = plt.figure()
        fig.canvas.manager.full_screen_toggle()
        fig.suptitle(txt_file.split('/')[-1])
        fig.show()

        # Plot
        plt.subplot(grid_x, grid_y, i)
        plt.bar(["Pizzas", "T2", "T3", "T4"], [m, t2, t3, t4])
        plt.title("Pizzas compared to team count")
        i += 1

        # Plot
        plt.subplot(grid_x, grid_y, i)
        plt.title("Ingredients")
        plt.bar([
            "Total",
            "Different"], [
            sum(number_of_ingredients_per_pizza),
            len(different_ingredients)])
        i += 1

        # Plot
        plt.subplot(grid_x, grid_y, i)
        plt.title("Ingredients")
        plt.bar([
            "Different per pizza",
            "Ingredients per pizza",
            "Different"], [
            len(different_ingredients) / len(number_of_ingredients_per_pizza),
            sum(number_of_ingredients_per_pizza) / len(number_of_ingredients_per_pizza),
            len(different_ingredients)])
        i += 1

        # Plot
        plt.subplot(grid_x, grid_y, i)
        plt.title("Ingredients")
        plt.bar([
            "Ingredients per pizza per different ingredients"], [
            sum(number_of_ingredients_per_pizza) / len(number_of_ingredients_per_pizza) / len(different_ingredients)])
        i += 1

        plt.show()

main()