import json
import os
import re
from glob import iglob

scopes: dict[str, str] = {
    'h': 'cpp',
    'hpp': 'cpp',
}

spec_pat = re.compile(r'^\s\* (.*): (.*)')
desc_pat = re.compile(r'^\s\* (.*)')
skip_pat = re.compile(r'^(?:#pragma|#include|.\*.|//NOLINT)')


def load_snippet(filename: str, prefix: str) -> dict[str, dict]:
    name, ext = os.path.basename(filename).rsplit('.', 1)
    meta: dict[str, str] = {}
    desc: list[str] = []  # Extracted from comment if not present (kactln't)
    body: list[str] = []

    with open(filename, "r") as f:
        last_meta: str | None = None
        for ln in f.readlines():
            spec_m = spec_pat.match(ln)
            if spec_m:
                # Spec in a comment (i.e. " * Description: ...")
                k, v = spec_m.groups()
                meta[k] = v

                last_meta = k
                continue

            desc_m = desc_pat.match(ln)
            if desc_m:
                # Miscellanous description in a comment
                desc.append(desc_m.group(1))
                last_meta = None
                continue

            if skip_pat.match(ln):
                if last_meta is not None:
                    # Continuation of description
                    meta[last_meta] += f" {ln.split('*')[1].strip()}"
                    last_meta = None
                continue

            last_meta = None
            body.append(ln)

    # Prefix description with time complexity if present
    description: str = ''
    if 'Time' in meta:
        description += f"{meta['Time']} | "
    description += meta.pop('Description', None) or ' '.join(desc)

    return {
        name: {
            'scope': scopes[ext],
            'prefix': [prefix + name],
            'body': body,
            'description': description,
        }
    }


def load_snippets(path: str, prefix: str) -> dict[str, dict]:
    res = {}
    for filename in iglob(path + '/**/*.*'):
        if not os.path.isfile(filename):
            continue

        ext = filename.rsplit('.', 1)[1]
        if ext in scopes:
            res.update(load_snippet(filename, prefix))

    return res


def dump_snippets(path: str, name: str):
    snippets = load_snippets(path, f'{name}_')

    with open(f'.vscode/{name}.code-snippets', 'w') as f:
        json.dump(snippets, f, indent=4)


if __name__ == '__main__':
    dump_snippets('hackpack/apoc/content', 'apoc')
    dump_snippets('hackpack/lrvideckis/library', 'lrv')
