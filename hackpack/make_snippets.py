# This is genuinely some of the worst code I've written in my life
# Don't read it please I'm sorry

import json
import os
import re
from glob import iglob

scopes: dict[str, str] = {
    'h': 'cpp',
    'hpp': 'cpp',
}

spec_pat = re.compile(r'^\s\* (.*): ?(.*)')
desc_pat = re.compile(r'^\s\* (.*)')
skip_pat = re.compile(r'^(?:#pragma|#include|.\*.?|//NOLINT)')
code_pat = re.compile(r'^\s\*\s@code')
end_spec_pat = re.compile(r'^(?:#pragma|#include|//NOLINT|\s\*/)')
omit_tex_pat = re.compile(r'(?:\\(?=[^(?:le|ge)])|\$)')


def load_snippet(filename: str, prefix: str, is_apoc: bool) -> dict[str, dict]:
    name, ext = os.path.basename(filename).rsplit('.', 1)
    meta: dict[str, str] = {}
    desc: list[str] = []  # Extracted from comment if not present (kactln't)
    body: list[str] = []

    with open(filename, "r") as f:
        if not is_apoc:
            # lol
            is_code = False
            code = []
            for ln in f.readlines():
                if code_pat.match(ln):
                    is_code = True
                    continue

                if skip_pat.match(ln):
                    is_code = False
                    continue

                if is_code:
                    code.append(ln.strip())
                    continue

                body.append(ln.replace('ssize', 'sz').rstrip())
            if code:
                body += ['#if 0'] + code + ['#endif']

        else:
            last_meta: str | None = None
            for ln in f.readlines():
                spec_m = spec_pat.match(ln)
                if spec_m:
                    # Spec in a comment (i.e. " * Description: ...")
                    k, v = spec_m.groups()
                    if k == 'Usage':
                        meta[k] = ['/*', ' * Usage: ' + v.rstrip()]
                    else:
                        meta[k] = v.rstrip()

                    last_meta = k
                    continue

                if skip_pat.match(ln):
                    if last_meta is not None:
                        # Continuation of spec
                        if last_meta == 'Usage':
                            meta[last_meta].append(ln.rstrip())
                        else:
                            meta[last_meta] += f" {ln.split('*')[1].strip()}"
                    if end_spec_pat.match(ln):
                        last_meta = None
                    continue
                if last_meta is not None and re.match(r'^\s\w', ln):
                    # Continuation of spec without the leading asterisk
                    if last_meta == 'Usage':
                        meta[last_meta].append(ln.rstrip())
                    else:
                        meta[last_meta] += f' {ln.strip()}'
                    continue

                desc_m = desc_pat.match(ln)
                if desc_m:
                    # Miscellanous description in a comment
                    desc.append(desc_m.group(1).strip())
                    last_meta = None
                    continue

                last_meta = None
                body.append(ln.rstrip())

    # Remove leading/trailing empty strings from body
    while body and not body[0].strip():
        body.pop(0)
    while body and not body[-1].strip():
        body.pop()

    # Prefix description with time complexity if present
    description: str = ''
    if 'Time' in meta:
        description += meta['Time'] + ' | '
    description += meta.get('Description', None) or ' '.join(desc)
    description = omit_tex_pat.sub('', description)

    # Prepend usage to body if present
    usage: list[str] = meta.get('Usage', [])
    if usage:
        usage.append(' */')

    return {
        name: {
            'scope': scopes[ext],
            'prefix': [prefix + name],
            'body': usage + body,
            'description': description,
        }
    }


def load_snippets(path: str, prefix: str, is_apoc: bool) -> dict[str, dict]:
    res = {}
    for filename in iglob(path + '/**/*.*'):
        if not os.path.isfile(filename):
            continue

        ext = filename.rsplit('.', 1)[1]
        if ext in scopes:
            res.update(load_snippet(filename, prefix, is_apoc))

    return res


def dump_snippets(path: str, name: str, is_apoc: bool = False) -> None:
    snippets = load_snippets(path, f'{name}_', is_apoc)

    with open(f'.vscode/{name}.code-snippets', 'w') as f:
        json.dump(snippets, f, indent=4)


if __name__ == '__main__':
    dump_snippets('hackpack/apoc/content', 'apoc', True)
    dump_snippets('hackpack/lrvideckis/library', 'lrv')
