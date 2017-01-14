<?php $person = new Roller();
	//$person->startup();
	//echo "\n_name:".$person->_name."\n";
    //$person->sname("mickelfeng"); 
	//echo "\n";
	//echo $person->gname()."\n<br/>";
	//$person->_controller = "aaaaa";
	//echo $person->_controller."\r\n";
	$person->sayroute('/hm/Index/ct/test/mt/init/');

	echo $person->_controller."\n".$person->_home."\n".$person->_method."\n";



