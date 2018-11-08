<?php
include_once 'includes/db_connect.php';
include_once 'includes/functions.php';

?>
<!DOCTYPE html>
<html>
    <head>
        <meta charset="UTF-8">
        <title>Secure Login: Reset Form</title>
        <script type="text/JavaScript" src="js/sha512.js"></script>
        <script type="text/JavaScript" src="js/forms.js"></script>
        <link rel="stylesheet" href="styles/main.css" />
    </head>
    <body>
        <h1>Forgot Password?</h1>
        <?php
        if (!empty($error_msg)) {
            echo $error_msg;
        }
        ?>

        <form method="post" name="registration_form" action="includes/process_reset.php">
            Email: <input type="text" name="email" id="email" /><br>
            New Password: <input type="password"
                             name="password"
                             id="password"/><br>
            Confirm password: <input type="password"
                                     name="confirmpwd"
                                     id="confirmpwd" /><br>
            Security Question : <select name="security_ques" id="security_ques">
                <option value="What was your childhood nickname?">What was your childhood nickname?</option>
                <option value="What is the name of your favorite childhood friend?">What is the name of your favorite childhood friend?</option>
                <option value="What is your favorite movie?">What is your favorite movie?</option>
                <option value="What was your favorite food as a child?">What was your favorite food as a child?</option>
                <option value="Who is your childhood sports hero?">Who is your childhood sports hero?</option>

                      </select> <br>
            Security Answer : <input id="security_ans" type="text" name="security_ans">
            <input type="button"
                   value="Register"
                   onclick="return regformhash(this.form,
                                   this.form.email,
                                   this.form.password,
                                   this.form.confirmpwd,
                                   this.form.security_ques,
                                   this.form.security_ans);" />
        </form>
        <p>Return to the <a href="index.php">login page</a>.</p>
    </body>
</html>
