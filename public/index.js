$("#formMain").submit(function (event) {
    event.preventDefault();
    let name = $("#inputName").val();
    console.log(name);
    //let data = {name : name};
    if (name !== "") {
        console.log("click");
        $.ajax({
            type: $(this).attr('method'),
            url: $(this).attr('action'),
            contentType: "application/json",
            data: JSON.stringify({"name": name}),
            success: function (result) {
                if (result.hasUser) {
                    $("#result").text("Пользователь есть");
                } else {
                    $("#result").text("Такого пользователя нет");
                }
            }
        })
    }

})