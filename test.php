<?php $person = new Roller();
	$person->startup();
	echo "\n_name:".$person->_name."\n";
    $person->sname("mickelfeng"); 
	echo "\n";
	echo $person->gname()."\n<br/>";
	$person->_controller = "aaaaa";
	echo $person->_controller."\r\n";



