if ('speechSynthesis' in window){
    var msg = new SpeechSynthesisUtterance();
    msg.text = "Good Morning";
    window.speechSynthesis.speak(msg); 
} else {
    alert('O navegador nao suporta a fala :/');
}