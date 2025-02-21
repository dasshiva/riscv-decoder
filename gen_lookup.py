file = open("lookup.h", "w")
file.write("#ifndef __LOOKUP_H__\n")
file.write("#define __LOOKUP_H__\n")
file.write("#include \"lookup_structs.h\"\n")

sorted_ops = [3, 7, 9, 15, 19, 23, 27, 35,
                39, 47, 51, 51, 55, 59, 67, 71, 75,
                79, 83, 99, 103, 111, 115] 
                
file.write("#endif\n")