const {contextBridge,ipcRenderer}=require('electron');
contextBridge.exposeInMainWorld('electronAPI',{
save_file: ()=>ipcRenderer.invoke('save-file'),
delete_node: ()=>ipcRenderer.invoke('delete-node'),
find_fish: ()=>ipcRenderer.invoke('find-fish'),
create_fish: ()=>ipcRenderer.invoke('create-fish'),
change_fish: ()=>ipcRenderer.invoke('change-fish'),
load_file: ()=>ipcRenderer.invoke('load-file'),
})