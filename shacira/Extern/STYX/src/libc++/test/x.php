#!/usr/bin/php
<aif<
<if<
<?php

$aa = 1;

print $aa -= 1 ? "aa=true\n" : "aa=false\n";

printf("IS_NULL\n");
$a = '';
print_r(is_null($a));
//exit(0);

$a = array(1,2,3,4);

$k = array_search(2,$a);
echo $k;

$s = "";
if( $s )
  echo "true\n";
else echo "false\n";

$b =& $a[9];
if( !$b )
  echo "undefined\n";

$b =& $c[9];
if( !$b )
  echo "undefined 2\n";

$b = "a";
print_r(${$b});

$c = './context.inc';

class y
{
  function y()
  {
  }

  function a($a1)
  {
    printf("a: a1=$a1\n");
  }

  function a1($a1,$a2)
  {
    printf("X: a1=${a1} a2={$a2} a: a1=$a1,a2=$a2\n");
    printf(
<<< etx
       ABER HALLO '`"
       if
       <=
       $!
       $a1
       $(a1)
       {$a1}
       ${a1}------------>----
oho

etx
    );
  }
}

function x()
{ 
  global $c;
  //require_once "context.inc";
  require_once $c;
  global $context;
  printf("CONTEXT:\n");
  print_r($context->getTitle());
  printf("\n");
  print_r($context->getErrorIdTyp());
  printf("\n");

  if( function_exists(false) )
    call_user_fun("hallo");

  $x = $a[9]['a'][0];
  if( !$x )
    echo "undefined ->3\n";
}

x();

$bb=array();
printf("BB=\n");
print_r(strlen($bb));
print_r(strlen($xx));
printf("\n");
if( !$bb )
printf("!BB\n");
printf("is_number\n");
print_r(is_numeric(1.2));
printf("\n");
print_r(is_numeric('1'));
printf("\n");
print_r(is_numeric('a'));
printf("\n");
$v = setlocale("LC_ALL",0);
printf("$v\n");
//$t = mktime(0,0,0,13,12,2002);
$t = mktime(18,0,6,1,1,2000);
//print_r(date('Y-m-d',$t));
print_r(date('H-i-s',$t));
printf("\n");

$o = new y();
$o->a("hallo");
$o->a1("hallo","welt");
$t = mktime(0,0,0,4,22,1960);
print_r(date('Y-m-d',$t));

$aa = array('hh' => 1, 'gg' => 2);
printf("AA=%s\n",array_shift($aa));

$cc =& $aa['gg'];
printf("$cc\n");
$cc = 3;
printf("$cc\n");
printf("%s\n",$aa['gg']);

//fehler

?>

