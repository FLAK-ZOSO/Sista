# SPDX-FileCopyrightText: 2026 FLAK-ZOSO <mattia.marchese.2006@gmail.com>
# SPDX-License-Identifier: GPL-3.0-only

"""Run with an installed extension, or PYTHONPATH pointing to python/src."""
import os
import subprocess
import sys
import unittest

import sista


class HyperlinkTests(unittest.TestCase):
    def test_native_output(self):
        # Native C++ output does not pass through Python's sys.stdout.
        result = subprocess.run(
            [sys.executable, "-c",
             "import sista; "
             "assert sista.print_hyperlink('Sista 🌍', 'https://example.com/path%20name') is None; "
             "sista.print_hyperlink(url='', text=''); "
             "sista.print_hyperlink('next', 'https://example.com/next')"],
            check=True, capture_output=True,
        )
        self.assertEqual(result.stdout,
                         b'\x1b]8;;https://example.com/path%20name\x1b\\' +
                         'Sista 🌍'.encode() + b'\x1b]8;;\x1b\\' +
                         b'\x1b]8;;\x1b\\\x1b]8;;\x1b\\' +
                         b'\x1b]8;;https://example.com/next\x1b\\next\x1b]8;;\x1b\\')

    def test_argument_types(self):
        for args in [(None, 'url'), ('text', None), (1, 'url'),
                     (b'text', 'url'), ('text',), ('text', 'url', 'extra')]:
            with self.subTest(args=args), self.assertRaises(TypeError):
                sista.print_hyperlink(*args)
        with self.assertRaises(TypeError):
            sista.print_hyperlink(text='text', url='url', unexpected=True)

    def test_embedded_nul(self):
        for args in [('text\0tail', 'url'), ('text', 'url\0tail')]:
            with self.subTest(args=args), self.assertRaises(ValueError):
                sista.print_hyperlink(*args)

    @unittest.skipUnless(os.environ.get('SISTA_C_HYPERLINK_TEST'),
                         'Set SISTA_C_HYPERLINK_TEST to the compiled C test')
    def test_c_api_output(self):
        result = subprocess.run([os.environ['SISTA_C_HYPERLINK_TEST']],
                                check=True, capture_output=True)
        self.assertEqual(result.stdout,
                         b'\x1b]8;;https://example.com/path%20name\x1b\\Sista\x1b]8;;\x1b\\'
                         b'\x1b]8;;\x1b\\\x1b]8;;\x1b\\')


if __name__ == '__main__':
    unittest.main()
