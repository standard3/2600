import functools
import inspect

def checktypes(func):
    @functools.wraps(func)
    def wrapper(*args, **kwargs):
        fun_ref = func(*args, **kwargs)

        # Check parameters
        signatures = inspect.signature(func)
        parameters = signatures.parameters

        for count, param in enumerate(parameters):
            arg_hint   = type(args[count])
            param_hint = signatures.parameters[param].annotation

            if not param_hint == signatures.empty and arg_hint != param_hint:
                raise TypeError(f"wrong type of '{param}' argument, '{param.__class__.__name__}' expected, got '{args[count].__class__.__name__}'")

        # Check return
        return_value_type = type(fun_ref)
        return_hint = signatures.return_annotation

        if not return_hint == signatures.empty and return_hint != return_value_type:
            raise TypeError(f"wrong return type, '{return_hint.__name__}' expected, got '{fun_ref.__class__.__name__}'")

        return fun_ref

    return wrapper