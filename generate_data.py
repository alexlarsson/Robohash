import sys
import os
import subprocess
import re

colors = ['blue','brown','green','grey','orange','pink','purple','red','white','yellow']
elements = ['003#01Body', '004#02Face', '000#Mouth', '001#Eyes', '002#Accessory', ]

num_elements = -1

print "static const unsigned char robot_data[] = "
set_data = []
part_data = []
element_data = []
offset = 0
col = 0;

def print_file (path):
    global col
    f = open(path, "rb")
    data = f.read()
    f.close()

    for c in data:
        if col == 0:
            sys.stdout.write ('    "')
        sys.stdout.write("\\x%02x" % ord(c))
        col = col + 1
        if col == 20:
            print '"'
            col = 0

    return len(data)

for i in range(0, len(colors)):
    color = colors[i]
    set_data = set_data + [color]
    part_data = part_data + [[]]
    element_data = element_data + [[]]
    for j in range(0,len(elements)):
        element = elements[j]
        element_data[i] = element_data[i] + [re.sub("[\d#]+", "", element)]
        part_data[i] = part_data[i] + [[]]
        path = color + "/" + element
        listdir = os.listdir(path)
        for f in listdir:
            if f.endswith(".png"):
                size = print_file (path + "/" + f)
                part_data[i][j] = part_data[i][j] + [(size, offset)]
                offset = offset + size

if col != 0:
    print '";'
else:
    print ";"

print '''
typedef struct {
   int size;
   int offset;
} RobohashPart;

typedef struct {
   int n_parts;
   const RobohashPart *parts;
} RobohashElement;

typedef struct {
   int n_elements;
   const RobohashElement **elements;
} RobohashSet;

'''

for i in range(0, len(set_data)):
    for j in range(0,len(element_data[i])):
        num_parts = len(part_data[i][j])
        print "static const RobohashPart %s_%s_parts[] = {" % (set_data[i], element_data[i][j])
        for k in range(0,num_parts):
            print "  { %d, %d }," % (part_data[i][j][k][0], part_data[i][j][k][1])
        print "};";
        print "static const RobohashElement %s_%s_element = { %d, %s_%s_parts};" % (set_data[i], element_data[i][j], num_parts, set_data[i], element_data[i][j])
    print "static const RobohashElement *%s_elements[] = {" % (set_data[i])
    for j in range(0,len(elements)):
        print "  &%s_%s_element," % (set_data[i], element_data[i][j])
    print "};"
    print "static const RobohashSet %s_set = { %d, %s_elements};" % (set_data[i], len(element_data[i]), set_data[i])

print "static const RobohashSet *all_sets[] = {"
for i in range(0, len(set_data)):
    print "  &%s_set," % (set_data[i])
print "};"
