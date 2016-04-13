#! /usr/bin/env python

latlong = open('info.txt','r')
infile = open('Earthquakes.txt','r')
outfile = open('LatLongMag.data','w')

values = latlong.read().replace('\n', '').split(',')
earthquakes = infile.read().split('\n')

cnt = 0

final = ''

for val in values:
    val = val.split()
    for row in earthquakes:
        row = row.split()
        if len(row) >= 4:
            if val[0] == row[1] and val[1] == row[2]:
                stri = row[1] + ' ' + row[2] + ' ' + row[3] + ' ' + row[0] + '\n'
                final = final + stri
                cnt = cnt + 1

outfile.write(str(cnt) + '\n')
outfile.write(final)

infile.close()
latlong.close()
outfile.close()
