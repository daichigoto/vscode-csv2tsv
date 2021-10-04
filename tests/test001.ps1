$f = New-TemporaryFile

.\csv2tsv.exe .\data\data.csv > $f

C:\Windows\System32\fc.exe .\data\data.tsv $f > $null

if ($?) {
	echo 'テスト001: 成功'
}
else {
	echo 'テスト001: 失敗'
}

Remove-Item $f
