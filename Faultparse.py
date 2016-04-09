
outfile = open('Fault_proc.data', 'w')
ml_bit = 0
fault_count = 0

with open('Fault.data') as f:
    for line in f:
        data = line.strip()
        if data == '':
            continue
        if ml_bit == 1:
            entire += data[1:-2].strip().replace(', ', ';').replace(' ', ',')
            if data[-2:] == "))":
                ml_bit = 0
                entire = entire + ")\n"
                outfile.write(entire)
            else:
                entire += ";"
            continue
        if data.split(' ')[0] == "LINESTRING":
            fault_count += 1
            data = data[10:].strip().replace(', ', ';').replace(' ', ',')            
            outfile.write(data+"\n")
        elif data.split(' ')[0] == "MULTILINESTRING":
            ml_bit = 1
            fault_count += 1
            entire = data[17:-1].strip().replace(', ', ';').replace(' ', ',')
            entire = entire[:-1]+";"

outfile.close()
outfile = open('Fault_final.data', 'w')
outfile.write(str(fault_count)+"\n")

with open('Fault_proc.data') as f:
    for line in f:
        data = line.strip()[1:-1].split(';')
        outfile.write(str(len(data))+"\n")
        for entry in data:
            outfile.write(entry.replace(',', ' ')+"\n")
