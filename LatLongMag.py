#! /usr/bin/env python

from xlrd import open_workbook

book = open_workbook('Indian-Earthquakes-List-Update_Magnitudes.xls', on_demand=True)
latlong = open('info.txt','r')
outfile = open('LatLongMag.data','w')

values = latlong.read().replace('\n', '').split(',')

sheet = book.sheet_by_name('EQs') 

cnt = 0
for val in values:
    print cnt
    r = 0
    val = val.split()
    for lat in sheet.col(11):
        lat = lat.value
        if float(val[0]) == lat and float(val[1]) == sheet.col(12)[r].value:
            stri = str(lat) + str(sheet.col(12)[r].value) + str(sheet.col(6)[r].value) + '\n'
            outfile.write(stri)
        r = r + 1
    cnt = cnt+1

latlong.close()
outfile.close()
