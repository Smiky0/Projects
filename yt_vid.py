'''Make sure pytube and moviepy is installed!'''
# If not installed use [pip install pytube] same for moviepy to install them
from pytube import YouTube
from moviepy.editor import *
import os
link = input("Video Link: ")
yt = YouTube(link)

"""
Pros: 
    Download audio files only
    Download high resolution videos
Cons:
    No progress bar while downloading
    Merging audio and video files takes time while downloading videos
    Custom file name after downloading video files
"""
# I will try to fix these cons on future :)
# Hope you like using it!


def get_audio():
    # get the audio file downloaded
    try:
        aud = yt.streams.filter(type="audio")
        print("Your audio file will be downloaded shortly. Please wait a lil !")
        # get it downloaded in the same folder as before
        # aud_file[-1].download(dir)
        aud[-1].download()
        print("Audio file:%s \nDownloaded sucessfully." % yt.title)
        print("---------------------------------")
    except:
        print("Couldn't download")
        print("Make sure you are connected to the internet and the given link is valid!")


def get_video():
    # get the video file downloaded
    try:
        while 1:
            # get the preferred resolution from user
            resolution = input(
                "Resolution(360p/480p/720p/1080p/1440p/2160p): ")
            # filter streams
            video = yt.streams.filter(res=resolution, mime_type="video/mp4")
            # check of the given resolution is available or not
            if not video:
                print("Resolution unavailable! Please choose another.")
                print("---------------------------------")
            else:
                break
        print("---------------------------------")
        print("Downloading:", yt.title)
        print("---------------------------------")
        print("Your video file will be downloaded shortly. Please wait a lil !")
        # get any vid codec from the list
        # download on current directory
        video_file = video[-1].download(filename="yt_vid.mp4")
        # download on a different directory
        #dir = input("Directory: ")
        # video_file[-1].download(dir)
        print("Video file sucessfully downloaded.")
        print("---------------------------------")

    except:
        print("Couldn't download!")
        print("Make sure you are connected to the internet and the given link is valid!")

    # get the audio file downloaded
    try:
        aud = yt.streams.filter(type="audio")
        print("Your audio file will be downloaded shortly. Please wait a lil !")
        # get it downloaded in the same folder as before
        # aud_file[-1].download(dir)
        aud_file = aud[-1].download(filename="yt_aud.mp3")
        print("Audio file downloaded sucessfully.")
        print("---------------------------------")
    except:
        print("Couldn't download")
        print("Make sure you are connected to the internet and the given link is valid!")


choice = input("Download AUDIO/VIDEO(1/0): ")
# you can download the audio only if you want
if choice == 1:
    get_audio()
    exit(0)
else:
    get_video()

# merge both audio and video file
print("---------------------------------")
print("Hold tight! We will merge the audio and video file together")
print("---------------------------------")
clip = VideoFileClip("yt_vid.mp4")
audioclip = AudioFileClip("yt_aud.mp3")
videoclip = clip.set_audio(audioclip)
print("---------------------------------")

videoclip.write_videofile("yt_video.mp4")
# remove the audio file and vid file....  after our merging is done
os.remove("yt_aud.mp3")
os.remove("yt_vid.mp4")
print("Completely merged! Ready to watch and play.")
