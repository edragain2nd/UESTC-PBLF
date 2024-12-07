const { appendFile } = require("original-fs");

class fish_node{
    constructor(fish_name,catch_time,length,width,profile)
    {
        this.fish_name=fish_name;
        this.catch_time=catch_time;
        this.length=length;
        this.width=width;
        this.profile=profile;
        this.next=null;
    }
}
class fish_link
{
constructor()
{
this.head=null;
}
append_fish(fish_name,catch_time,length,width,profile)
{
}
delete(fish_name)
{
}
find_fish(fish_name)
{
}
change_fish(fish_name,newfish_name,newcatch_time,newlength,newwidth,newprofile)
{
}
savetoload(filename)
{
}
load_file(filename)
{
}
}
const fish_link1= new fish_link();

