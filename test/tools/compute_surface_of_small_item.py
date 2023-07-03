import numpy as np
from itertools import chain

def flatten(ls):
    return list(chain(*ls))

def Surface(item_size, item_position):
    l, w, h = [item_size[prop] for prop in ["l", "w", "h"]]
    px, py, pz = [item_position[prop] for prop in ["x", "y", "z"]]
    print(l, w, h)
    return np.array([px, py, pz]) + np.array(flatten([
            np.array([[  x,   y,   0] for x in range(0, l) for y in range(0, w)]) + np.array([  0,  0,  -1]),
            np.array([[  x,   y, h-1] for x in range(0, l) for y in range(0, w)]) + np.array([  0,  0,  +1]),
            np.array([[  x,   0,   z] for x in range(0, l) for z in range(0, h)]) + np.array([  0, -1,   0]),
            np.array([[  x, w-1,   z] for x in range(0, l) for z in range(0, h)]) + np.array([  0, +1,   0]),
            np.array([[  0,   y,   z] for y in range(0, w) for z in range(0, h)]) + np.array([ -1,  0,   0]),
            np.array([[l-1,   y,   z] for y in range(0, w) for z in range(0, h)]) + np.array([ +1,  0,   0])
        ]))

def vector_to_string(arr):
    return "{" + "{:2d}, {:2d}, {:2d}".format(arr[0], arr[1], arr[2]) + "}"

def print_array_of_vectors(arr):
    print("{\n\t" + ",\n\t".join([vector_to_string(x) for x in arr]) + "\n}")

if __name__ == '__main__':
    item_size = {
        "l": 2,
        "w": 3,
        "h": 5
    }

    item_position = {
        "x": 7,
        "y": 11,
        "z": 13
    }

    S = Surface(item_size, item_position)
    print_array_of_vectors(S)
