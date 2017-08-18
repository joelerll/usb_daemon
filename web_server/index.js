// console.log('afdfsds')

$(document).ready(function() {
    $('#boton').click(function() {
        $.ajax({
            method: 'GET',
            url: '/api/listar_dispositivos',
            success: function(data) {
                console.log(data);
            },
            error: function(xhr, status, error) {
                console.log(xhr);
                console.log(status + '; ' + error);
            }
        })
    })
});
