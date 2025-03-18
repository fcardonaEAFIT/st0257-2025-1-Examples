#!/usr/bin/python3
from functools import reduce

def first_fit(mem_avail, req_size, index):
    searching = True
    found = False
    i = index
    while searching:
        if mem_avail[i][1] >= req_size:
            found = True
            break
        i = (i + 1) % len(mem_avail)
        if i == index:
            searching = False

    if found:
        base = mem_avail[i][0]
        limit = req_size
        if mem_avail[i][1] == req_size:
            del mem_avail[i]
        else:
            mem_pos = mem_avail[i]
            mem_avail[i] = (mem_pos[0] + req_size, mem_pos[1] - req_size) 
        return mem_avail, base, limit, i

    return None

def best_fit(mem_avail, req_size, index):
    searching = True
    found = False
    i = index
    min_val = pow(2,32) - 1 
    min_idx = i
    while searching:
        if mem_avail[i][1] <= min_val and mem_avail[i][1] >= req_size:
            min_val = mem_avail[i][1]
            min_idx = i
            found = True
        i = (i + 1) % len(mem_avail)
        if i == index:
            searching = False

    if found:
        base = mem_avail[min_idx][0]
        limit = req_size
        if mem_avail[min_idx][1] == req_size:
            del mem_avail[i]
        else:
            mem_pos = mem_avail[min_idx]
            mem_avail[min_idx] = (mem_pos[0] + req_size, mem_pos[1] - req_size) 
        return mem_avail, base, limit, min_idx

    return None

def worst_fit(mem_avail, req_size, index):
    searching = True
    found = False
    i = index
    max_val = 0
    min_idx = i
    while searching:
        if mem_avail[i][1] > max_val and mem_avail[i][1] >= req_size:
            min = mem_avail[i][1]
            min_idx = i
            found = True
        i = (i + 1) % len(mem_avail)
        if i == index:
            searching = False

    if found:
        base = mem_avail[min_idx][0]
        limit = req_size
        if mem_avail[min_idx][1] == req_size:
            del mem_avail[i]
        else:
            mem_pos = mem_avail[min_idx]
            mem_avail[min_idx] = (mem_pos[0] + req_size, mem_pos[1] - req_size) 
        return mem_avail, base, limit, min_idx

    return None

def print_memory_map(memory_map):
    for memory in memory_map:
        print(f"({hex(memory[0])}, {hex(memory[1])})")

memory = [(0x06D01000, 0x00500000),
          (0x06100C00, 0x00C00000),
          (0x05200400, 0x00F00000),
          (0x04800000, 0x00A00000),
          (0x01E00000, 0x00400000),
          (0x02500000, 0x01400000),
          (0x07201800, 0x01200000),
          (0x08402C00, 0x00700000)]
first_pos = 0

requirements = [0x00C00000, 0x00A00000, 0x00B00000]
work_memory = memory[:]

index = first_pos
print("First fit")
print_memory_map(work_memory)

for req in requirements:
    search = first_fit(work_memory, req, index)

    if search == None:
        print(f"Not found: {req:#0{8}x}")
    else:
        print(f"Assigned to the process base: {search[1]:#0{8}x} limit: {search[2]:#{8}x}")
        print(f"Index: {search[3]}")
        print_memory_map(search[0])
        index = search[3]

work_memory = memory[:]
index = first_pos
print("Best fit")
print_memory_map(work_memory)

for req in requirements:
    search = best_fit(work_memory, req, index)

    if search == None:
        print(f"Not found: {req:#0{8}x}")
    else:
        print(f"Assigned to the process base: {search[1]:#0{8}x} limit: {search[2]:#{8}x}")
        print(f"Index: {search[3]}")
        print_memory_map(search[0])
        index = search[3]

work_memory = memory[:]
index = first_pos
print("Worst fit")
print_memory_map(work_memory)

for req in requirements:
    search = worst_fit(work_memory, req, index)

    if search == None:
        print(f"Not found: {req:#0{8}x}")
    else:
        print(f"Assigned to the process base: {search[1]:#0{8}x} limit: {search[2]:#{8}x}")
        print(f"Index: {search[3]}")
        print_memory_map(search[0])
        index = search[3]
