#include <string>
#include <iostream>
#include <fstream>
#include <cstring>
#include <exception>
#include <cassert>
#include <unistd.h>

template <std::size_t N>
int execvp(const char *file, const char *const (&argv)[N])
{
    assert((N > 0) && (argv[N - 1] == nullptr));

    return execvp(file, const_cast<char *const *>(argv));
}

struct VIDException : public std::exception
{
    const char *what() const throw()
    {
        return "VID not found in /proc/bus/input/devices, please make sure your Dualsense is connected";
    }
};

std::string get_device(std::string device_vid, std::string device_pid)
{
    std::ifstream file_input;
    std::size_t pos;
    std::string device_path, current_line, search_str, event_str;
    std::string device_list_file = "/proc/bus/input/devices";
    bool vid_pid_found = false;
    bool debug = false;

    // 1. open device list file
    file_input.open(device_list_file.c_str());
    if (!file_input.is_open())
    {
        std::cerr << "file_input.open >> " << std::strerror(errno) << std::endl;
        throw -2;
    }

    // 2. search for first VID:PID and get event number
    search_str = "Vendor=" + device_vid + " Product=" + device_pid;
    while (getline(file_input, current_line))
    {
        if (!vid_pid_found)
        {
            pos = current_line.find(search_str, 0);
            if (pos != std::string::npos)
            {
                vid_pid_found = true;
                search_str = "event";
            }
        }
        else
        {
            pos = current_line.find(search_str, 0);
            if (pos != std::string::npos)
            {
                event_str = current_line.substr(pos);
                // find space and substring event##
                pos = event_str.find(' ', 0);
                event_str = event_str.substr(0, pos);
                break;
            }
        }
    }
    if (!vid_pid_found)
        throw VIDException();

    // 3.  build device path
    device_path = "evdev=/dev/input/" + event_str;
    if (debug)
        std::cout << device_path << std::endl;

    return device_path;
}

int main(int argc, char* argv[])
{
    try
    {
        std::string event_path = get_device("054c", "0ce6");
        if (argc < 2) {
            execvp("xboxdrv", 
            {"xboxdrv", 
            "-o", event_path.c_str(), 
            "--mimic-xpad",
            "--silent",
            "--quiet",
            "--axismap",
            "-y1=y1,-y2=y2",
            "--evdev-absmap",
            "ABS_HAT0X=dpad_x,ABS_HAT0Y=dpad_y,ABS_X=X1,ABS_Y=Y1,ABS_RX=X2,ABS_RY=Y2,ABS_Z=LT,ABS_RZ=RT",
            "--evdev-keymap", 
            "BTN_SOUTH=A,BTN_EAST=B,BTN_NORTH=Y,BTN_WEST=X,BTN_START=start,BTN_MODE=guide,BTN_SELECT=back,BTN_TL=LB,BTN_TR=RB,BTN_TL2=LT,BTN_TR2=RT,BTN_THUMBL=TL,BTN_THUMBR=TR",
            nullptr}
            );
        }
        else {
            execvp("xboxdrv", {"xboxdrv", "-c", argv[1], "-o", event_path.c_str(), nullptr});
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
        return 1;
    }
    return 0;
}