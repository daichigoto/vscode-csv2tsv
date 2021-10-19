$n = '004'
$d = 'empty'
$f = New-TemporaryFile

.\csv2tsv.exe .\data\${d}.csv > $f

C:\Windows\System32\fc.exe .\data\${d}.tsv $f > $null

if ($?) {
	echo "テスト${n}: 成功"
}
else {
	echo "テスト${n}: 失敗"
}

Remove-Item $f
