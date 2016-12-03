<?php 

$MyUsername = "root";  
$MyPassword = "YourPassHere"; 
$MyHostname = "localhost";      
$MyDBName = "M2M";
 

$conn = new mysqli($MyHostname, $MyUsername, $MyPassword, $MyDBName);
// Check connection
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 



?>