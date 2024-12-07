const {contextBridge,ipcRenderer}=require('electron');
const api={
append_fish:(fish_name,catch_time,length,width,profile)=>ipcRenderer.invoke('',fish_name,catch_time,length,width,profile),
delete_fish:(fish_name)=>ipcRenderer.invoke('',fish_name),
find_fish:(fish_name)=>ipcRenderer.invoke('',fish_name),
change_fish:(fish_name,newfish_name,newcatch_time,newlength,newwidth,newprofile)=>ipcRenderer.invoke('',fish_name,newfish_name,newcatch_time,newlength,newwidth,newprofile),
savetoload:(filename)=>ipcRenderer.invoke('',filename),
load_file:(filename)=>ipcRenderer.invoke('',filename),
};
contextBridge.exposeInMainWorld('electronAPI', api);