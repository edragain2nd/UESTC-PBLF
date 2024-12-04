const { app, BrowserWindow } = require('electron/main')
const path=require('path')
app.on('ready',()=>
{
    const win =new BrowserWindow(
        {
            width:800,
            height:600,
            autoHideMenuBar:true,
            alwaysOnTop:true,
            x:0,
            y:0
        }
    )
    win.loadFile('./index.html')
})
