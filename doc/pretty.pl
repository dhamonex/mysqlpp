use FileHandle;
use IPC::Open2;

if ($ARGV[0] =~ /^--command\=(.+)/) {
    $command = $1;
} else {
    $command = "g++ -E";
}

$/ = undef;
$orgcode = <STDIN>;

($macro) = $orgcode =~ /(sql_create_.+? *\(.+?\))/s;

$out = << "---";

#include <mysql++-int/custom-macros.hh>

$macro

---

$/ = "\n";

$temp_dir = -d '/tmp' ? '/tmp' : $ENV{TMP} || $ENV{TEMP};

#print $out;

open OUT, ">$temp_dir/${$}.cc";
print OUT $out;
close OUT;

system "$command $temp_dir/${$}.cc > $temp_dir/${$}.ii";

open IN, "$temp_dir/${$}.ii";
while (<IN>) {
    next if /^\#/;    
    $code .= $_;
}
close IN;

unlink "$temp_dir/${$}.cc","$temp_dir/${$}.ii";

$_ = $code;
s/\s+/ /g;
s/ *public: */public:\n/g;
s/ *private: */public:\n/g;
s/ *\; */\;\n/g;
s/ *\{ */ \{\n/g;
s/ *\} */ \}\n\n/g;
s/ *\n */\n/g;
s/\{\s+}/\{\}/g;
s/\}\s+\;/\}\;\n/g;

$code = "";
foreach (split /\n/) {
    if (/\}/ && !/\{\}/ ) {
	$indent -= 2;
	$ind = ' 'x$indent;
    }
    $code .= "$ind$_\n" unless /\:$/;
    $code .= "$_\n"     if     /\:$/;
    if (/\{/ && !/\{\}/ ) {
	$indent += 2;
	$ind = ' 'x$indent;
    } 
}

$orgcode =~ s/(sql_create_.+? *\(.+?\))/\n$code\n/s;

print $orgcode;




