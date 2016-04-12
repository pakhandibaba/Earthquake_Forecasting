#! /usr/bin/env python

latlong = open('info.txt','r')
infile = open('Earthquakes.txt','r')
outfile = open('LatLongMag.data','w')

values = latlong.read().replace('\n', '').split(',')
earthquakes = infile.read().split('\n')

for val in values:
    val = val.split()
    for row in earthquakes:
        row = row.split()
        if len(row) >= 3:
            if val[0] == row[0] and val[1] == row[1]:
                stri = row[0] + '\n' + row[1] + '\n' + row[2] + '\n'
                outfile.write(stri)

infile.close()
latlong.close()
outfile.close()
