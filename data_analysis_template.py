from os import listdir
from os.path import isfile, join
import numpy as np
import matplotlib.pyplot as plt



def plotData(datas, titles, grid_x, grid_y):
    x_labels = [chr(97+i) for i in range(len(datas[0]))]
    for i in range(grid_x * grid_y):
        data = len(datas[0]) * [0]
        title = ""
        if i < len(datas):
            data = datas[i]
        if i < len(titles):
            title = titles[i]
        plt.subplot(grid_x, grid_y, i+1)
        plt.bar(x_labels, data)
        plt.title(title)
    plt.show()


def createData(txt_files):
    datas = [ extractFile(txt_file) for txt_file in txt_files ]
    grouped_data = []
    for i in range(len(datas[0])):
        data_group = [ datas[j][i] for j in range(len(datas)) ]
        grouped_data.append(data_group)
    return grouped_data


# Read data and return list of integers of the analyzed data
def extractFile(file_name):
    street_name_time = {}
    max_score = 0
    with open(file_name) as file:
        lines = file.readlines()
        for i, line in enumerate(lines):
            if line == '\n':
                continue
            line = [ x for x in line.strip("\n").split(' ') ]
            if i == 0:
                duration = int(line[0])
                num_intersections = int(line[1])
                num_streets = int(line[2])
                num_cars = int(line[3])
                bonus = int(line[4])
            else:
                if num_streets:
                    num_streets -= 1
                    start_i = int(line[0])
                    end_i = int(line[1])
                    street_name = line[2]
                    street_time = int(line[3])
                    street_name_time[street_name] = street_time
                elif num_cars:
                    num_cars -= 1
                    car_path = line[1:]
                    path_duration = 0
                    for street_name in car_path:
                        path_duration += street_name_time[street_name]
                    if path_duration <= duration:
                        max_score += bonus + (duration - path_duration)
    return [
        max_score,
    ]


def main():
    root = "input_files"
    txt_files = sorted([
        join(root, f) for f in listdir(root) if isfile(join(root, f))])
    grid_x = 3
    grid_y = 3
    datas = createData(txt_files)

    # Define titles
    titles = [
        "Max score = {:,}".format(sum(datas[0])),
    ]
    plotData(datas, titles, grid_x, grid_y)


main()
