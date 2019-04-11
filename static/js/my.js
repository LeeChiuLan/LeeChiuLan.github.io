//JS操作cookies方法!
//寫cookies
function setCookie(name, value, expiredays=365){
    var d = new Date();
    d.setTime(d.getTime() + (expiredays * 24 * 60 * 60 * 1000));
    var expires = "expires=" + d.toGMTString();
    document.cookie = name + "=" + value + "; " + expires;
    // alert(document.cookie)
}
//讀取cookies
function getCookie(cname){
    var name = cname + "=";
    var ca = document.cookie.split(';');
    for(var i=0; i<ca.length; i++) 
    {
    var c = ca[i].trim();
    if (c.indexOf(name)==0) return c.substring(name.length,c.length);
    }
    return "";
}
//刪除cookies
function delCookie(name){
    var d = new Date();
    d.setTime(d.getTime() - 1);
    var expires = "expires=" + d.toGMTString();
    var value=getCookie(name);
    if(value!=null)
        document.cookie= name + "=" + value + "; " + expires;
}