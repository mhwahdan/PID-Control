from django.urls import path

from PID import views


urlpatterns = [
    path('', views.index, name="home"),
    path('control/', views.start_pid, name="startPID"),
    path('plot/', views.get_point, name="plot")
]