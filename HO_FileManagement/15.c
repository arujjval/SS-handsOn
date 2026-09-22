#include <stdio.h>

// env. variables: name=value type info that current process can use
// environ: variable, used to access all env. variables of current process
// It is pointer to an array of pointers to strings


// extern: variable already exists elsewhere, use that. No new define
// since environ is predefined global variable
extern char **environ;

int main() {
    char **env = environ;

    while (*env != NULL) {
        printf("%s\n",*env);
        env++;
    }

    return 0;
}

// OUTPUT 
// arujjval@arujjval:~/SS/HO_FileManagement$ ./a.out 
// SHELL=/bin/bash
// COLORTERM=truecolor
// WSL2_GUI_APPS_ENABLED=1
// TERM_PROGRAM_VERSION=1.138.0
// COPILOT_DEBUG_NONCE=bf57d32c194ec6a1b044c26e18679c53
// WSL_DISTRO_NAME=Ubuntu-24.04
// NAME=arujjval
// PWD=/home/arujjval/SS/HO_FileManagement
// LOGNAME=arujjval
// VSCODE_GIT_ASKPASS_NODE=/home/arujjval/.vscode-server/bin/7debcd0e2acdea1c52de81bf9ee1620444407dda/node
// HOME=/home/arujjval
// LANG=C.UTF-8
// WSL_INTEROP=/run/WSL/10904_interop
// LS_COLORS=rs=0:di=01;34:ln=01;36:mh=00:pi=40;33:so=01;35:do=01;35:bd=40;33;01:cd=40;33;01:or=40;31;01:mi=00:su=37;41:sg=30;43:ca=00:tw=30;42:ow=34;42:st=37;44:ex=01;32:*.tar=01;31:*.tgz=01;31:*.arc=01;31:*.arj=01;31:*.taz=01;31:*.lha=01;31:*.lz4=01;31:*.lzh=01;31:*.lzma=01;31:*.tlz=01;31:*.txz=01;31:*.tzo=01;31:*.t7z=01;31:*.zip=01;31:*.z=01;31:*.dz=01;31:*.gz=01;31:*.lrz=01;31:*.lz=01;31:*.lzo=01;31:*.xz=01;31:*.zst=01;31:*.tzst=01;31:*.bz2=01;31:*.bz=01;31:*.tbz=01;31:*.tbz2=01;31:*.tz=01;31:*.deb=01;31:*.rpm=01;31:*.jar=01;31:*.war=01;31:*.ear=01;31:*.sar=01;31:*.rar=01;31:*.alz=01;31:*.ace=01;31:*.zoo=01;31:*.cpio=01;31:*.7z=01;31:*.rz=01;31:*.cab=01;31:*.wim=01;31:*.swm=01;31:*.dwm=01;31:*.esd=01;31:*.avif=01;35:*.jpg=01;35:*.jpeg=01;35:*.mjpg=01;35:*.mjpeg=01;35:*.gif=01;35:*.bmp=01;35:*.pbm=01;35:*.pgm=01;35:*.ppm=01;35:*.tga=01;35:*.xbm=01;35:*.xpm=01;35:*.tif=01;35:*.tiff=01;35:*.png=01;35:*.svg=01;35:*.svgz=01;35:*.mng=01;35:*.pcx=01;35:*.mov=01;35:*.mpg=01;35:*.mpeg=01;35:*.m2v=01;35:*.mkv=01;35:*.webm=01;35:*.webp=01;35:*.ogm=01;35:*.mp4=01;35:*.m4v=01;35:*.mp4v=01;35:*.vob=01;35:*.qt=01;35:*.nuv=01;35:*.wmv=01;35:*.asf=01;35:*.rm=01;35:*.rmvb=01;35:*.flc=01;35:*.avi=01;35:*.fli=01;35:*.flv=01;35:*.gl=01;35:*.dl=01;35:*.xcf=01;35:*.xwd=01;35:*.yuv=01;35:*.cgm=01;35:*.emf=01;35:*.ogv=01;35:*.ogx=01;35:*.aac=00;36:*.au=00;36:*.flac=00;36:*.m4a=00;36:*.mid=00;36:*.midi=00;36:*.mka=00;36:*.mp3=00;36:*.mpc=00;36:*.ogg=00;36:*.ra=00;36:*.wav=00;36:*.oga=00;36:*.opus=00;36:*.spx=00;36:*.xspf=00;36:*~=00;90:*#=00;90:*.bak=00;90:*.crdownload=00;90:*.dpkg-dist=00;90:*.dpkg-new=00;90:*.dpkg-old=00;90:*.dpkg-tmp=00;90:*.old=00;90:*.orig=00;90:*.part=00;90:*.rej=00;90:*.rpmnew=00;90:*.rpmorig=00;90:*.rpmsave=00;90:*.swp=00;90:*.tmp=00;90:*.ucf-dist=00;90:*.ucf-new=00;90:*.ucf-old=00;90:
// WAYLAND_DISPLAY=wayland-0
// GIT_ASKPASS=/home/arujjval/.vscode-server/bin/7debcd0e2acdea1c52de81bf9ee1620444407dda/extensions/git/dist/askpass.sh
// VSCODE_GIT_ASKPASS_EXTRA_ARGS=
// VSCODE_PYTHON_AUTOACTIVATE_GUARD=1
// LESSCLOSE=/usr/bin/lesspipe %s %s
// TERM=xterm-256color
// LESSOPEN=| /usr/bin/lesspipe %s
// USER=arujjval
// VSCODE_GIT_IPC_HANDLE=/run/user/1000/vscode-git-d57196b5af.sock
// DISPLAY=:0
// SHLVL=1
// XDG_RUNTIME_DIR=/run/user/1000/
// WSLENV=VSCODE_WSL_EXT_LOCATION/up
// VSCODE_GIT_ASKPASS_MAIN=/home/arujjval/.vscode-server/bin/7debcd0e2acdea1c52de81bf9ee1620444407dda/extensions/git/dist/askpass-main.js
// PATH=/home/arujjval/.local/bin:/home/arujjval/.vscode-server/data/User/globalStorage/github.copilot-chat/debugCommand:/home/arujjval/.vscode-server/data/User/globalStorage/github.copilot-chat/copilotCli:/home/arujjval/.vscode-server/bin/7debcd0e2acdea1c52de81bf9ee1620444407dda/bin/remote-cli:/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin:/usr/games:/usr/local/games:/usr/lib/wsl/lib:/mnt/c/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.0/bin/x64:/mnt/c/Program Files/NVIDIA GPU Computing Toolkit/CUDA/v13.0/bin:/mnt/c/Users/arujj/AppData/Local/Programs/cursor/resources/app/bin:/mnt/c/Program Files/BraveSoftware/Brave-Browser/Application:/mnt/c/Windows/system32:/mnt/c/Windows:/mnt/c/Windows/System32/Wbem:/mnt/c/Windows/System32/WindowsPowerShell/v1.0/:/mnt/c/Windows/System32/OpenSSH/:/mnt/c/Program Files (x86)/NVIDIA Corporation/PhysX/Common:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/Git/cmd:/mnt/c/Users/arujj/AppData/Local/nvm:/mnt/c/nvm4w/nodejs:/mnt/c/Users/arujj/AppData/Local/Microsoft/WindowsApps:/mnt/c/WINDOWS/system32:/mnt/c/WINDOWS:/mnt/c/WINDOWS/System32/Wbem:/mnt/c/WINDOWS/System32/WindowsPowerShell/v1.0/:/mnt/c/WINDOWS/System32/OpenSSH/:/mnt/c/Program Files/NVIDIA Corporation/Nsight Compute 2025.3.1/:/mnt/c/Program Files (x86)/GnuPG/bin:/mnt/c/Program Files/Docker/Docker/resources/bin:/mnt/c/Program Files/NVIDIA Corporation/NVIDIA App/NvDLISR:/mnt/c/msys64/ucrt64/bin:/mnt/c/Program Files/nodejs/:/mnt/c/Users/arujj/AppData/Local/Programs/Python/Python313/Scripts/:/mnt/c/Users/arujj/AppData/Local/Programs/Python/Python313/:/mnt/c/Users/arujj/AppData/Local/Programs/Python/Launcher/:/mnt/c/Users/arujj/AppData/Local/Microsoft/WindowsApps:/mnt/c/Users/arujj/AppData/Local/Programs/cursor/resources/app/bin:/mnt/c/Users/arujj/AppData/Local/Programs/Ollama:/mnt/c/Users/arujj/AppData/Local/Programs/Microsoft VS Code/bin:/mnt/c/Users/arujj/AppData/Local/Programs/Antigravity IDE/bin:/mnt/c/msys64/usr/bin:/mnt/c/Users/arujj/AppData/Roaming/npm
// DBUS_SESSION_BUS_ADDRESS=unix:path=/run/user/1000/bus
// HOSTTYPE=x86_64
// PULSE_SERVER=unix:/mnt/wslg/PulseServer
// TERM_PROGRAM=vscode
// VSCODE_IPC_HOOK_CLI=/run/user/1000/vscode-ipc-9ae1c593-2421-4ea4-87c3-0c351ea9d526.sock
// OLDPWD=/home/arujjval/SS/HO_FileManagement/1
// _=./a.out