<?php
// the PHP strpos() function to check whether a string contains a specific word or not.
// echo str_replace("world","Peter","Hello world!");
// Replace the characters "world" in the string "Hello world!" with "Peter":

function make_link($lnk,$x,$y,$s){
global $_SERVER;

$url='';
if (strpos($_SERVER['REQUEST_URI'],"index.php?admin"))
   {  $url="http://".$_SERVER['SERVER_NAME'].str_replace("index.php?admin","",$_SERVER['REQUEST_URI']); };
if (strpos($_SERVER['REQUEST_URI'],"index.php?studenti"))
   {  $url="http://".$_SERVER['SERVER_NAME'].str_replace("index.php?studenti","",$_SERVER['REQUEST_URI']); };
if (strpos($_SERVER['REQUEST_URI'],"index.php?catalog"))
   {  $url="http://".$_SERVER['SERVER_NAME'].str_replace("index.php?catalog","",$_SERVER['REQUEST_URI']); };
if (strpos($_SERVER['REQUEST_URI'],"admin.php"))
   {  $url="http://".$_SERVER['SERVER_NAME'].str_replace("admin.php","",$_SERVER['REQUEST_URI']); };
if (strpos($_SERVER['REQUEST_URI'],"catalog/catalog.php"))
   {  $url="http://".$_SERVER['SERVER_NAME'].str_replace("catalog/catalog.php","",$_SERVER['REQUEST_URI']); };
if (strpos($_SERVER['REQUEST_URI'],"stud/vizualizare.php"))
   {  $url="http://".$_SERVER['SERVER_NAME'].str_replace("stud/vizualizare.php","",$_SERVER['REQUEST_URI']); };


if (strpos($_SERVER['REQUEST_URI'],"admin.php"))
{return $url.$lnk;}
else {return "javascript:popUp('".$url.$lnk."','$x','$y','$s')";}
}

function popupjs(){
?>
<SCRIPT LANGUAGE="JavaScript">
<!-- Begin
function popUp(URL,sx,sy,scr) {
opt = 'toolbar=0,scrollbars='+scr+',location=1,statusbar=1,menubar=0,resizable=0,width='+sx+',height='+sy+',left = 376,top = 232';
day = new Date();
id = day.getTime();
eval("page" + id + " = window.open(URL, '" + id + "', opt);");
}
// End -->
</script>
<?php
}

?>