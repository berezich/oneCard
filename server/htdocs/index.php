<?php
header('Content-type: text/plain; charset=utf-8');
echo "<?xml version=\"1.0\" encoding=\"UTF-8\" ?>\r\n";
$reqType = htmlspecialchars( $_GET["action"] );
$login = htmlspecialchars( $_GET["login"] );
$pass = htmlspecialchars( $_GET["pass"] );

if($login != "oneCard" || $pass != "123456" )
{
	$xml="";
	die(make_err_xml("1","authentication failed!"));
}

switch(strtolower($reqType))
{
	
	case "getgrp":
		db_get_grps();
		break;
	case "getcards":
		$grp_id = $_GET["grpid"];
		db_get_cards_info($grp_id);
		break;
	default:
		die(make_err_xml("2","invalid reqType!"));
		
	
}
function db_connect()
{
	$servername = "mysql.bsvgrip.mass.hc.ru";
	$username = "bsvgrip";
	$password = "wze1Shae";
	$dbname = "wwwbsvgripcom";
	// Create connection
	$conn = new mysqli($servername, $username, $password, $dbname);
	$conn->set_charset("utf8");
	// Check connection
	if ($conn->connect_error) {
		die(make_err_xml("100","Connection failed: ".$conn->connect_error));
	}
	else
	{
		//echo "Connection established!";
	}
	return $conn;
}
function db_get_grps($conn)
{
	$conn = db_connect();
	$sql = "SELECT * FROM oneCard_grps";
	$result = $conn->query($sql);
	echo result_to_xml($result,"groups","grp");
	$conn->close();
}
function db_get_cards_info($grp_id)
{
	$conn = db_connect();
	$sql = "SELECT * FROM oneCard_cards WHERE GRP_ID = " . $grp_id;
	$result = $conn->query($sql);
	echo result_to_xml($result,"cards","card");
	$conn->close();
}
function result_to_xml($res,$table_name,$item_name)
{
	if($table_name!="")
		$xml="<". $table_name .">";
	$finfo = $res->fetch_fields();
	$cnt_finfo = count($finfo);
	if ($res->num_rows > 0) {
		// output data of each row
		while($row = $res->fetch_assoc()) {
			$xml.="<". $item_name .">";
			for($i=0; $i<$cnt_finfo; ++$i) 
			{
				$name = $finfo[$i]->name;
				$type = $finfo[$i]->type;
				if($type==252)// 252 === longblob type
					$xml.= "<" . $name . ">" . base64_encode($row[$name]) ."</" . $name . ">";
				else
					$xml.= "<" . $name . ">" . $row[$name] ."</" . $name . ">";
			}
			$xml.="</".$item_name.">";
		}
	} else {
		//echo "0 results";
	}
	if($table_name!="")
		$xml.="</". $table_name .">";
	return $xml;
}

function make_err_xml($code,$msg)
{
	return $xml = "<err><code>".$code."</code><msg>".$msg."</msg></err>";
}

		
?>