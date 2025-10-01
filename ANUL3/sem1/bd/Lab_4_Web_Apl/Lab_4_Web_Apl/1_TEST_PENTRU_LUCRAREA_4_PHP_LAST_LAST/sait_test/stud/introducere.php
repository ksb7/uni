<?php require_once('config.php');

/**
 * @author 
 * @copyright 2011
 */
 
if(!isset($_SESSION['student'])) $_SESSION['student'] = ''; 
if(!isset($_SESSION['datan'])) $_SESSION['datan'] = ''; 
if(!isset($_SESSION['an_inscriere'])) $_SESSION['an_inscriere'] = ''; 
if(!isset($_SESSION['e-mail'])) $_SESSION['e-mail'] = ''; 
if(!isset($_SESSION['telefon'])) $_SESSION['telefon'] = ''; 
if(!isset($_SESSION['mobil'])) $_SESSION['mobil'] = ''; 
if(!isset($_SESSION['obs'])) $_SESSION['obs'] = '';
echo '<table width="380" border="0" cellpadding="0" cellspacing="2"> <form name="stud" action="validare.php" method="post"> <tr>
<td height="30" colspan="2" valign="top"><h2>Introducere
Studenti</h2>	</td>
</tr> <tr>
<td  height="22" align="right" valign="top">Student:</td> <td  valign="top">
<input type="text" name="student" value="'.$_SESSION['student'].'">    </td> </tr>
<tr>
<td  height="22" align="right" valign="top">Data Nasterii:</td>
<td  valign="top"><input type="text" name="datan" value="'.$_SESSION['datan'].'"></td> </tr>
<tr>
<td height="22" align="right" valign="top">An inscriere: </td> <td valign="top"><input type="text" size="3" maxLength="3" name="an_ inscriere" value="'.$_SESSION['an_inscriere'].'"></td>
</tr>
<tr>
<td height="22" align="right" valign="top">E-mail:</td> <td valign="top"><input type="text" name="e-mail" value="'.$_SESSION['e-mail'].'"></td>
</tr>
<tr>
<td height="22" align="right" valign="top">Telefon:</td> <td valign="top"><input type="text" name="telefon" value="'.$_SESSION['telefon'].'"></td>
</tr>
<tr>
<td height="22" align="right" valign="top">Mobil:</td> <td valign="top"><input type="text" name="mobil" value="'.$_SESSION['mobil'].'"></td> </tr> <tr>
<td height="19" align="right" valign="top">Observatii:</td> <td rowspan="2" valign="top"><textarea name="obs" cols="30" rows="5" value="'.$_SESSION['obs'].'">'.$_SESSION['obs'].'</textarea></td>
</tr> <tr>
<td </td>
<td </td> </tr>
<tr>
<td  colspan="2" valign="top"><input name="Trimite" type="submit" id="Trimite" value="Trimite">
<input name="Reseteaza" type="reset" id="Reseteaza" value="Reseteaza"> </td>
</tr> </form> </table>';


?>