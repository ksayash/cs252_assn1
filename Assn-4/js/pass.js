function editDistance(s1, s2) {
  s1 = s1.toLowerCase();
  s2 = s2.toLowerCase();

  var costs = new Array();
  for (var i = 0; i <= s1.length; i++) {
    var lastValue = i;
    for (var j = 0; j <= s2.length; j++) {
      if (i == 0)
        costs[j] = j;
      else {
        if (j > 0) {
          var newValue = costs[j - 1];
          if (s1.charAt(i - 1) != s2.charAt(j - 1))
            newValue = Math.min(Math.min(newValue, lastValue),
              costs[j]) + 1;
          costs[j - 1] = lastValue;
          lastValue = newValue;
        }
      }
    }
    if (i > 0)
      costs[s2.length] = lastValue;
  }
  return costs[s2.length];
}
function similarity(s1, s2) {
  var longer = s1;
  var shorter = s2;
  if (s1.length < s2.length) {
    longer = s2;
    shorter = s1;
  }
  var longerLength = longer.length;
  if (longerLength == 0) {
    return 1.0;
  }
  return (longerLength - editDistance(longer, shorter)) / parseFloat(longerLength);
}
function checkStrength() {
	var pass = document.getElementById('password').value;

	if(pass.length < 7){
		document.getElementById('pass-strength').innerHTML = `Enter ${8 -1 - pass.length} more characters`;
		document.getElementById('pass-strength').style.color = 'red';
		return ;
	}
	var common_pass = ['password', '123456', '12345678', '12345', 'qwerty', 'abc123', 'football', 'monkey', '123456789', '1234567', 'letmein', '111111', '1234', '1234567890', 'dragon', 'baseball', 'trustno1', 'iloveyou', 'princess', 'adobe123[a]', '123123', 'welcome', 'login', 'admin', 'solo', 'master', 'sunshine', 'photoshop[a]', '1qaz2wsx', 'ashley', 'mustang', '121212', 'starwars', 'bailey', 'access', 'flower', 'passw0rd', 'shadow', 'michael', '654321', 'jesus', 'password1', 'superman', 'hello', '696969', 'qwertyuiop', 'hottie', 'freedom', 'qazwsx', 'ninja', 'azerty', 'loveme', 'whatever', 'batman', 'zaq1zaq1', 'Football', '000000']

	for (var i = 0; i < common_pass.length; i++) {
		if (similarity(common_pass[i], pass) > 0.7) {
			console.log(111111);
			document.getElementById('pass-strength').innerHTML = `Weak, much similar to <i>` +  common_pass[i] + '</i>';
			document.getElementById('pass-strength').style.color = 'red';
			return ;
		}
	}
	for (var i = 0; i < common_pass.length; i++) {
		if (similarity(common_pass[i], pass) > 0.3){
			document.getElementById('pass-strength').innerHTML = `Medium`;
			document.getElementById('pass-strength').style.color = 'orange';
			return ;
		}
	}

	document.getElementById('pass-strength').innerHTML = `Strong`;
	document.getElementById('pass-strength').style.color = 'green';
}
