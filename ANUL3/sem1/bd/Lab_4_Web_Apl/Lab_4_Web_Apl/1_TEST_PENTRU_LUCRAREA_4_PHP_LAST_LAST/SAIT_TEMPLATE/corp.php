<?php
/* PREZENTARE PARTE MENIU VERTICAL */
echo'<body> 
<table border="1" width="705" align="center">
<tr>
   <td valign="top" width="70">';
     if (file_exists("meniu_vertical.html"))
         {
			 include("meniu_vertical.html");      
	     } 
/* PREZENTARE PARTE PAGINA */
echo' 
</td>
     <td width="">';
if (file_exists("pagina.php"))
         {     
             include_once("pagina.php");   
		 } 
echo '
     </td> 
	    </tr> 
</table>'; 
echo'</body>';
?>
