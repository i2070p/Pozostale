#!/user/bin/perl


if (!(@ARGV == 2 or @ARGV == 1)) {
	die "Nieprawidłowa liczba parametrów (2 wymagane)";
}

if (@ARGV == 1) {
	$path=$ARGV[0];
} else {
	if (substr($ARGV[0], 0, 1) eq '-') {
		$path=$ARGV[1];
		$param=substr($ARGV[0], 1, 1)
	} elsif (substr($ARGV[1], 0, 1) eq '-') {
		$path=$ARGV[0];
		$param=substr($ARGV[1], 1, 1);
	} else {
		die "Nieprawidłowy format parametrów (-l, -L, nazwa)";
	}

	if ($param ne 'L' and $param ne 'l') {
		die "Nieznany parametr ".$param;	
	}
}


opendir $h, $path or die "...\n";

@t= sort readdir $h;

@syms = ('x','w','r');
$bits = 9;

foreach $el(@t) {
  ($mode, $size, $m_time, $own_id)=(stat $el)[2, 7, 9, 4];
  @t_el = localtime($m_time);
    

  $p = sprintf("%04d-%02d-%02d %02d:%02d:%02d", 
	$t_el[5]+1900, 
	$t_el[4]+1, 
	$t_el[3], 
	$t_el[2], 
	$t_el[1], 
	$t_el[0]);
  $perm ="";

  for ($i=0; $i<$bits; $i++) {
     if ($mode & (0x01 << $i)) {
       $perm.=$syms[$i % @syms];
     } else {
       $perm.='-';
     }
  }

  if (-d $el) {
 	$perm.='d'; 
  } else {
        $perm.='-';
  }

  $perm = reverse $perm;
  print $el;
  if ($param eq 'l' or $param eq 'L') {
	  print ", Size: ".$size.", MTime: ".$p.", Perm ".$perm;
	  if ($param eq 'L') {
		print ", Owner:".getpwuid($own_id);
	  }
  }

  print "\n";
}

closedir $h;
