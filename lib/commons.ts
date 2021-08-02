import path from 'path'

export function resolvePath(filePath?: string, file?: string): string {
  if (!filePath) {
    return ''
  }
  return (file ? path.resolve(filePath, file) : path.resolve(filePath)).replace(/\\/g, '/')
}
