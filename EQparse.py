
outfile = open('EQ_proc.data', 'w')

count = 0
with open('EQ.data') as f:
    for line in f:
        data = line.strip()
        if data == '':
            continue
        count += 1
        data = data.split(' ')[1:]
        outfile.write(",".join(data)+"\n")

outfile.close()
outfile = open('EQ_final.data', 'w')
outfile.write(str(count)+"\n")
with open('EQ_proc.data') as f:
    for line in f:
        data = line.strip()
        data = data[1:-1].replace(',', ' ')
        outfile.write(data+"\n")
        
