from django.shortcuts import render

# Create your views here.
import subprocess

from django.http import HttpResponse, HttpResponseRedirect

def index(request):
    return render(request, 'Map.html', {})

def process(request):
    coor = request.GET['latlong']
    lat, longi = coor.strip().split(" ")
    year = request.GET['year']
    args = ("./a.out", "Earthquakes.txt", "Fault_final.data", year, longi, lat)
    popen = subprocess.Popen(args, stdout=subprocess.PIPE)
    popen.wait()
    output = popen.stdout.read()
    output = output.replace("\n", "<br>")
    return HttpResponse(output)
